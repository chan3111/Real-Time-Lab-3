#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

volatile sig_atomic_t usr1Happened = 0;
sem_t *sem;

void* childThread(void* arg){
	printf("Child thread %d created\n", pthread_self());

	while(1){
		sem_wait(sem);
		printf("Child Thread %d unblocked\n", pthread_self());
		sleep(5);
	}

	return NULL;
}

void handler(){
	usr1Happened = 1;
}

int main(int argc, char *argv[]) {
	int numThreads = 0;
	int i;

	struct sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	pthread_attr_t attr;

	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		perror("sigaction");
		exit(1);
	}

	printf("Enter the number of threads to create:\n");
	scanf("%d", &numThreads);

	sem = sem_open("SEM1", O_CREAT, S_IWOTH, 0);

	for(i = 0; i < numThreads; i++){
		pthread_attr_init(&attr);
		pthread_create(NULL, &attr, &childThread, NULL);
		pthread_attr_destroy(&attr);
	}

	while(usr1Happened != 1);

	sem_close(sem);
	sem_destroy(sem);
	return EXIT_SUCCESS;
}
