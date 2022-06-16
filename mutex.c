#include <stdio.h>
#include <pthread.h>

#define COUNT 1000
#define LOOP 10000

pthread_mutex_t mutex;

struct timespec ts[5][COUNT];

void busy(){
	for(int i=0; i<LOOP; i++){}	
}

void *func(void *arg){
	int thn=(int)arg;
	int ts_index=0;
	for(int i=0; i<10; i++){
		pthread_mutex_lock(&mutex);
		for(int j=0; j<100; j++){
			busy();
			clock_gettime(CLOCK_REALTIME, &ts[thn][ts_index]);
			ts_index++;		
		}
		pthread_mutex_unlock(&mutex);
		busy();
	}	
}

int main(){
	struct timespec x;
	clock_gettime(CLOCK_REALTIME, &x);	//start
	long startt=x.tv_sec * 1000000000 + x.tv_nsec;
	pthread_t th0;
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_create(&th0, NULL, func, (void *)0);
	pthread_create(&th1, NULL, func, (void *)1);
	pthread_create(&th2, NULL, func, (void *)2);
	pthread_create(&th3, NULL, func, (void *)3);
	
	pthread_join(th0,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);

	for(int thn=0; thn<5; thn++){
		for(int i=0; i<COUNT; i++){
			long t=ts[thn][i].tv_sec * 1000000000 + ts[thn][i].tv_nsec;
			printf("%d\t%d\n", t-startt, thn);
		}
	}
	return 0;
}
