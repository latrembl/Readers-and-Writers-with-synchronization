#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 10
#define NUM_WRITERS 2
#define NUM_READS 5
#define NUM_WRITES 5
#define SEM_NAME "/SEM_latrembl"

typedef struct {
	pthread_mutex_t *mutex;
	sem_t *rw_sem;
	int readerCount;
} SyncInfo;

typedef struct {
	SyncInfo *syncInfo;
	char myName[32];
} ThreadInfo;

void *reader(void *data);
void *writer(void *data);

