#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *sem;

int main(int argc, char *argv[]) {
	int numWakeup = 0;
	int i;

	sem = sem_open("SEM1", 0);
	printf("Program 2 PID: %d\n", getpid());

	do{
		printf("How many threads would you like to wake up (enter 0 to exit): \n");
		scanf("%d", &numWakeup);

		for(i = 0;i < numWakeup; i++){
			sem_post(sem);
		}
	}while(numWakeup != 0);

	sem_close(sem);
	sem_destroy(sem);
	return EXIT_SUCCESS;
}
