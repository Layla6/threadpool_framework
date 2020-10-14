#include<pthread.h>
#include<iostream>
using namespace std;

static pthread_mutex_t mtx1=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx2=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx3=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t conda=PTHREAD_COND_INITIALIZER;
static pthread_cond_t condb=PTHREAD_COND_INITIALIZER;
static pthread_cond_t condc=PTHREAD_COND_INITIALIZER;
void * functionA(void*){
	int i=10;
	while(i--){
		pthread_mutex_lock(&mtx1);
		pthread_cond_wait(&condc,&mtx1);
		cout<<"A"<<endl;
		pthread_mutex_unlock(&mtx1);
		pthread_cond_signal(&conda);
	}	
}
void * functionB(void*){
	int i=10;
	while(i--){
		pthread_mutex_lock(&mtx2);
		pthread_cond_wait(&conda,&mtx2);
		cout<<"B"<<endl;
		pthread_mutex_unlock(&mtx2);
		pthread_cond_signal(&condb);
	}	
}
void * functionC(void*){
	int i=10;
	while(i--){
		pthread_mutex_lock(&mtx3);
		pthread_cond_wait(&condb,&mtx3);
		cout<<"C"<<endl;
		pthread_mutex_unlock(&mtx3);
		pthread_cond_signal(&condc);
	}	
}

int main(){
	pthread_t id1,id2,id3;
	pthread_create(&id1,NULL,functionA,NULL);
	pthread_create(&id2,NULL,functionB,NULL);
	pthread_create(&id3,NULL,functionC,NULL);
	pthread_cond_signal(&condc);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_join(id3,NULL);
	return 0;
}




