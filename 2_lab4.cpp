#include<iostream>
#include<pthread.h>
//#include<mythread.h>
#include<unistd.h>

using namespace std;

/*int n;
int flag[2];
int turn;
int self=0;
int self1=1;
void lock_init()
{
	flag[0]=flag[1]=0;
	turn =0;
}
void lock(int k)
{
	flag[k]=1;
	turn = 1-k;
	while(flag[1-k]==1 && turn ==1-k);
}
void unlock(int k)
{
	flag[k]=0;
}*/
bool lock=false;
int n;
bool TestAndSet(bool target){
	bool rv = target;
	target=true;
	return rv;
}
bool isprime(int n) 
{ 
    // Corner case 
    if (n <= 1) 
        return false; 
  
    // Check from 2 to n-1 
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false; 
  
    return true; 
} 
void* prime(void *arg)
{
	//int self=0;
	//lock(self);
	while(TestAndSet(lock))
		;
	for(int i=2;i<n;i++)
	{
		if(isprime(i))
		{
		  cout << i << " ";	
		}
	}
	cout << endl;
	//unlock(self);
	lock=false;
	//cout << lock << endl;
}
void* prime1(void *arg1)
{
	while(TestAndSet(lock))
		 ;
	for(int i=2;i<n;i++)
	{
		if(isprime(i))
		{
			printf("%.6f ",(float)n/(float)i);
		}
	}
	cout << endl;
	lock=false;
	//unlock(self1);
}
int main()
{
	pthread_t thread1,thread2;
	int *arg;
	int *arg1;
	//lock_init();
	cin >> n;
	pthread_create(&thread1,NULL,prime,(void *) arg);
	//pthread_create(&thread2,NULL,prime1,(void *) arg1);
	pthread_join(thread1,NULL);
	pthread_create(&thread2,NULL,prime1,(void *) arg1);
	pthread_join(thread2,NULL);
	return 1;
}
