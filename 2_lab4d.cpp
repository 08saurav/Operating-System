#include<iostream>
#include<pthread.h>
//#include<mythread.h>
#include<unistd.h>

using namespace std;


int s=1; 
int n;
void wait()
{
	while(s<=0);
	s--;
}
void signal()
{
	s++;
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
	wait();
	for(int i=2;i<n;i++)
	{
		if(isprime(i))
		{
		  cout << i << " ";	
		}
	}
	cout << endl;
	signal();
	//lock = false;
	//unlock(self);
}
void* prime1(void *arg1)
{
	wait();
	for(int i=2;i<n;i++)
	{
		if(isprime(i))
		{
			printf("%.6f ",(float)n/(float)i);
		}
	}
	cout << endl;
	signal();
}
int main()
{
	pthread_t thread1,thread2;
	int *arg;
	int *arg1;
	//lock_init();
	cin >> n;
	pthread_create(&thread1,NULL,prime,(void *) arg);
	pthread_create(&thread2,NULL,prime1,(void *) arg1);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 1;
}
