#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
void *func(int n);
pthread_t philosopher[10000];
pthread_mutex_t chopstick[10000];
int nphs;
void *func(int n)
{
	printf("\nPhilosopher %d is thinking ",n);
	pthread_mutex_lock(&chopstick[n]);//when philosopher 5 is eating he takes fork 1 and fork 5
	pthread_mutex_lock(&chopstick[(n+1)%nphs]);
	printf("\nPhilosopher %d is eating ",n);
	sleep(3);
	pthread_mutex_unlock(&chopstick[n]);
	pthread_mutex_unlock(&chopstick[(n+1)%nphs]);
	printf("\nPhilosopher %d Finished eating ",n);
}
int main()
{
	int i,k;
	void *msg;
	printf("Enter the number of philosphers\t");
	scanf("%d",&nphs);
	for(i=1;i<=nphs;i++)
	{
		k=pthread_mutex_init(&chopstick[i],NULL);
		if(k==-1)
		{
			printf("Mutex initialization failed");
			exit(1);
		}
	}
	for(i=1;i<=nphs;i++)
	{
		k=pthread_create(&philosopher[i],NULL,(void *)func,(int *)i);
		if(k!=0)
		{
			printf("\n Philosopher thread creation error \n");
			exit(1);
		}
	}
	for(i=1;i<=nphs;i++)
	{
		k=pthread_join(philosopher[i],&msg);
		if(k!=0)
		{
			printf("\n Philosopher thread join failed \n");
			exit(1);
		}
	}
	for(i=1;i<=nphs;i++)
	{
		k=pthread_mutex_destroy(&chopstick[i]);
		if(k!=0)
		{
			printf("\n Mutex Destroyed \n");
			exit(1);
		}
	}
	return 0;
}
