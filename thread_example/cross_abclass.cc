#pragma once(4)
#include<pthread.h>
#include<iostream>
#include "locker.h"

using namespace std;
cond a_cond,b_cond,c_cond;
void * functionA(void*){
	int i=10;
	while(i--){
		c_cond.wait();
		cout<<"A"<<endl;
		a_cond.signal();
	}	
}
void * functionB(void*){
	int i=10;
	while(i--){
		a_cond.wait();
		cout<<"B"<<endl;
		b_cond.signal();

	}	
}
void * functionC(void*){
	int i=10;
	while(i--){
		b_cond.wait();
		cout<<"C"<<endl;
		c_cond.signal();
	}	
}

int main(){
	pthread_t id1,id2,id3;
	pthread_create(&id1,NULL,functionA,NULL);
	pthread_create(&id2,NULL,functionB,NULL);
	pthread_create(&id3,NULL,functionC,NULL);
	c_cond.signal();
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_join(id3,NULL);
	return 0;
}




