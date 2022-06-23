#include <stdio.h>
#include <pthread.h>
#define N 10000

//initialize accounts
int account[100];
int from[N];
int to[N];
int amount[N];

pthread_mutex_t mutex;
pthread_cond_t cvar;

//toranzakusyon(thread)
//kouza hurikae
void *func(void *arg){
	int start=(int)arg * 1000;
	int end=start+999;				
	for(int i=start; i<end; i++)
	{
		int loop=amount[i] * 100;
		for(int j=0; j<loop; j++){}
		pthread_mutex_lock(&mutex);
		/*if(account[from[i]]==0){
			pthread_cond_wait(&cvar,&mutex);
		}*/
		while(account[from[i]]==0){
			pthread_cond_wait(&cvar,&mutex);		
		}
		account[from[i]]=account[from[i]]-amount[i];	
		account[to[i]]=account[to[i]]+amount[i];
		pthread_cond_signal(&cvar);
		pthread_mutex_unlock(&mutex);
	}
}

void sumAmount(){
	int sum=0;
	for(int i=0; i<100; i++){
		sum=sum+account[i];
	}
	printf("sumAmount: %d\n",sum);
}

int main(){	
	pthread_cond_init(&cvar,NULL);	
	struct timespec x;
	for(int i=0; i<100; i++){
		account[i]=10000;		
	}
	sumAmount();
	//road file
	FILE *istream;
	istream=fopen("trans.csv","r");
	if(istream==NULL){
		printf("can't open\n");
		return -1;	
	}
	char t;	//gomi
	int from_=0,to_=0,amount_=0;
	while(1){
		int val=fscanf(istream,"%c,%d,%d,%d,\n",&t,&from_,&to_,&amount_);
		if(val==EOF) break;
		for(int i=0; i<N; i++){
			from[i]=from_;
			to[i]=to_;	
			amount[i]=amount_;			
		}
	}
	fclose(istream);
	
	pthread_t th0;
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_t th4;
	pthread_t th5;
	pthread_t th6;
	pthread_t th7;
	pthread_t th8;
	pthread_t th9;
	
	clock_gettime(CLOCK_REALTIME, &x);	//start
	long startt=x.tv_sec * 1000000000 + x.tv_nsec;	
	pthread_create(&th0, NULL, func, (void *)0);
	pthread_create(&th1, NULL, func, (void *)1);
	pthread_create(&th2, NULL, func, (void *)2);
	pthread_create(&th3, NULL, func, (void *)3);
	pthread_create(&th4, NULL, func, (void *)4);
	pthread_create(&th5, NULL, func, (void *)5);
	pthread_create(&th6, NULL, func, (void *)6);
	pthread_create(&th7, NULL, func, (void *)7);
	pthread_create(&th8, NULL, func, (void *)8);
	pthread_create(&th9, NULL, func, (void *)9);	

	pthread_join(th0,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	pthread_join(th4,NULL);
	pthread_join(th5,NULL);
	pthread_join(th6,NULL);
	pthread_join(th7,NULL);
	pthread_join(th8,NULL);
	pthread_join(th9,NULL);
	clock_gettime(CLOCK_REALTIME, &x);	//start
	long endt=x.tv_sec * 1000000000 + x.tv_nsec;	
	printf("%ld\n",endt-startt);

	sumAmount();

	return 0;
}
