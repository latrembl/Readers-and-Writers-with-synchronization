#include "rw1.latrembl.h"

void *reader(void *data) {
	
	printf("---------------Hello from thread: %s------------------\n", ((ThreadInfo*)data)->myName);
	
	pthread_mutex_t *mutex;
	mutex = ((ThreadInfo*)data)->syncInfo->mutex;
	
	sem_t *rw_sem = ((ThreadInfo*)data)->syncInfo->rw_sem;
	
	int semVal;
	//sem_getvalue(((ThreadInfo*)data)->syncInfo->rw_sem, &semVal);
	sem_getvalue(rw_sem, &semVal);
	//printf("A - The value of the semaphore is %i \n", semVal);
	
	int numReaders = ((ThreadInfo*)data)->syncInfo->readerCount;
	//printf("The previous reader count was %i \n", numReaders);
	
	
	for (int i=0; i<NUM_READS; i++) {
		
		pthread_mutex_lock(mutex);
		numReaders ++;
		((ThreadInfo*)data)->syncInfo->readerCount++;
		printf("2 - This is reader #%i \n", ((ThreadInfo*)data)->syncInfo->readerCount);
		
		if (numReaders == 1) {
			
			// SEM WAIT-------------------------------------------------------------------------
			sem_wait(rw_sem);
			sem_getvalue(rw_sem, &semVal);
			//printf("B - The value of the semaphore is %i \n", semVal);
		}
		
		// signal/unlock mutex
		pthread_mutex_unlock(mutex);			
		printf("3 - Reading...\n");
		sleep(1);
		printf("4 - Reading Complete!\n");

		// wait/lock mutex
		pthread_mutex_lock(mutex);			
		// decrement numReaders
		numReaders --;
		//printf("5 - Current reader count = %i \n", numReaders);
		
		if (numReaders == 0) {
			// SEM POST------------------------------------------------------------------------
			sem_post(rw_sem);
			sem_getvalue(rw_sem, &semVal);
			//printf("C - The value of the semaphore is %i \n", semVal);			
		}
		//printf("Final Read Complete, Unlocking Mutex.\n");
		pthread_mutex_unlock(mutex);
	}	
			
	printf("---------------End of thread: %s------------------\n", ((ThreadInfo*)data)->myName);	
}
	
void *writer(void *data) {
	
	printf("---------------Hello from thread: %s------------------\n", ((ThreadInfo*)data)->myName);

	sem_t *rw_sem = ((ThreadInfo*)data)->syncInfo->rw_sem;
	
	//int semVal;
	//sem_getvalue(rw_sem, &semVal);
	//printf("A - The value of the semaphore is %i \n", semVal);		
	
	for (int i=0; i<NUM_WRITES; i++) {
		sem_wait(rw_sem);
		
		//sem_getvalue(rw_sem, &semVal);
		//printf("B - The value of the semaphore is %i \n", semVal);
		
		printf("Writing...\n");
		sleep(1);
		printf("Writing Complete!\n");
		
		sem_post(rw_sem);
		
		//sem_getvalue(rw_sem, &semVal);
		//printf("The value of the semaphore is %i \n", semVal);
	}
	
	printf("---------------End of thread: %s------------------\n", ((ThreadInfo*)data)->myName);
}

int main() {
	
	pthread_mutex_t mutex;
	sem_t *rw_sem;
	
	rw_sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, NULL, 1);	
	
	if (rw_sem == SEM_FAILED) {
		printf("sem_open() failed\n");
		sem_unlink(SEM_NAME);
		return(8);
	}
	
	SyncInfo *sync = (SyncInfo*) malloc(sizeof(SyncInfo*));
	pthread_mutex_init(&mutex, NULL);
	sync->mutex = &mutex;
	sync->rw_sem = rw_sem;
	sync->readerCount = 0;
	int count = sync->readerCount;
	
	// malloc ThreadInfo structs
	ThreadInfo *data1 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	ThreadInfo *data2 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	ThreadInfo *data3 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data4 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data5 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	ThreadInfo *data6 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data7 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data8 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data9 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));	
	ThreadInfo *data10 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	
	ThreadInfo *data11 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	ThreadInfo *data12 = (ThreadInfo*) malloc(sizeof(ThreadInfo*));
	
	// create 10 reader threads
	pthread_t readers[NUM_READERS];
	
	// create 2 writer threads
	pthread_t writers[NUM_WRITERS];	
	
	data1->syncInfo = sync;
	data2->syncInfo = sync;
	data3->syncInfo = sync;
	data4->syncInfo = sync;
	data5->syncInfo = sync;
	data6->syncInfo = sync;
	data7->syncInfo = sync;
	data8->syncInfo = sync;
	data9->syncInfo = sync;
	data10->syncInfo = sync;
	
	data11->syncInfo = sync;
	data12->syncInfo = sync;
	
	// naming threads
	char name1[32] = "Reader 1";
	strcpy(data1->myName, name1);
	char name2[32] = "Reader 2";
	strcpy(data2->myName, name2);
	char name3[32] = "Reader 3";
	strcpy(data3->myName, name3);
	char name4[32] = "Reader 4";
	strcpy(data4->myName, name4);
	char name5[32] = "Reader 5";
	strcpy(data5->myName, name5);
	char name6[32] = "Reader 6";
	strcpy(data6->myName, name6);
	char name7[32] = "Reader 7";
	strcpy(data7->myName, name7);
	char name8[32] = "Reader 8";
	strcpy(data8->myName, name8);
	char name9[32] = "Reader 9";
	strcpy(data9->myName, name9);
	char name10[32] = "Reader 10";
	strcpy(data10->myName, name10);
	
	char name11[32] = "Writer 1";
	strcpy(data11->myName, name11);
	char name12[32] = "Writer 2";
	strcpy(data12->myName, name12);
	
	// create reader threads
	pthread_create(&readers[0], NULL, reader, (void *)data1);
	pthread_create(&readers[1], NULL, reader, (void *)data2);	
	pthread_create(&readers[2], NULL, reader, (void *)data3);	
	pthread_create(&readers[3], NULL, reader, (void *)data4);	
	pthread_create(&readers[4], NULL, reader, (void *)data5);	
	pthread_create(&readers[5], NULL, reader, (void *)data6);	
	pthread_create(&readers[6], NULL, reader, (void *)data7);	
	pthread_create(&readers[7], NULL, reader, (void *)data8);	
	pthread_create(&readers[8], NULL, reader, (void *)data9);	
	pthread_create(&readers[9], NULL, reader, (void *)data10);	
	
	// create writer threads
	pthread_create(&writers[0], NULL, writer, (void *)data11);
	pthread_create(&writers[1], NULL, writer, (void *)data12);
	
	// joining threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL); 
	}	
	pthread_join(writers[0], NULL);
	pthread_join(writers[1], NULL);
	
	sem_close(rw_sem);
	sem_unlink(SEM_NAME);
	
	// free memory
	free(data1);
	free(data2);
	free(data3);
	free(data4);
	free(data5);
	free(data6);
	free(data7);
	free(data8);
	free(data9);
	free(data10);
	free(data11);
	free(data12);
	free(sync);
		
	return(0);	
}