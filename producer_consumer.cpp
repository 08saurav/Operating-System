#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

using namespace std;

// Structure of a Node
struct Node
{
    int data;
    struct Node* link;
};

typedef struct Queue
{
    struct Node *front, *rear;
}Queue;
int n;
typedef struct Node node;
node * temp = new node;
Queue *q=new Queue;
//q.front = q.rear=NULL;

// Function to create Circular queue
void *enQueue(void *t);
int deQueue(Queue *q);
void *displayQueue(void *arg);
int flag=0;
void thready_call()
{
pthread_t thread1,thread2;
	pthread_attr_t attr,attr1;
	void * status;
	//pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc;
	int *arg;
	rc=pthread_create(&thread1,NULL,enQueue,(void *) arg);
	if(rc){
		cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
	}
	//pthread_attr_destroy(&attr);
	rc = pthread_join(thread1,NULL);
	//pthread_attr_init(&attr1);
	rc=pthread_create(&thread2,NULL,displayQueue,(void *)arg);
	if(rc){
		cout << "Error:unable to create thread,"<< rc << endl;
		exit(-1);
	}
	//pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	pthread_exit(NULL);
}
void *enQueue(void *t)
{
	//void *p = (void *)arg;
	cout << "welcome to thread" << endl;
	cout << "enter the number of no. u want produce:  ";
	cin >> n;
	int g=n;
	if(flag==0)
	{
	q->front=q->rear=NULL;
	flag=1;
	}
	while(g--)
	{
	int k;
	cin >> k;
	node * temp = new node;
    	temp->data = k;
    	if (q->front == NULL)
        	q->front = temp;
    	else
        	q->rear->link = temp;

    	q->rear = temp;
    	q->rear->link = q->front;
	}
}

// Function to delete element from Circular Queue
int deQueue(Queue *q,int k)
{
    if (q->front == NULL)
    {
        printf ("Queue is empty");
        return -1;
    }

    // If this is the last node to be deleted
    int value; // Value to be dequeued
    /*if (q->front == q->rear)
    {
        value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    }
    else  // There are more than one nodes
    {
        node *temp = q->front;
        value = temp->data;
        q->front = q->front->link;
        q->rear->link= q->front;
        free(temp);
    }*/
    struct Node * temp = q->front;
    int g=k;
    if(n!=0)
    {
    while(k-->0 && q->front!=temp->link)
    {
	value = temp->data;
	cout << temp->data << " ";
	temp= temp->link;
    }
    cout << endl;
    if(g>=n)
    {
	cout << temp->data << endl;
	q->front=q->rear=NULL;
    }
    else
	    q->front=temp;
    }
    return value ;
}

// Function displaying the elements of Circular Queue
void *displayQueue(void *arg)
{
    //void *p = void *arg;
    int k,res=0;
    cout << "enter how many no. u want to consume:   ";
    cin >> k;
    int g = k;
   // cout << g << " " << n << endl;
    /*if(n!=0)
    {
    struct Node *temp = q->front;
    printf("\nElements in Circular Queue are: ");
    while (k-->0 && temp->link != q->front)
    {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    if(g==n || g>n)
    {
    printf("%d", temp->data);
    }
    cout << endl;
    }*/
    deQueue(q,k);
    cout << "Press (1) if u want to continue or press (0) if u want to terminate" << endl;
    cin >> res;
    if(res)
    {
	thready_call();
    }
}
void threadx_call()
{
pthread_t thread1,thread2;
	pthread_attr_t attr,attr1;
	void * status;
	//pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc;
	int *arg;
	rc=pthread_create(&thread1,NULL,enQueue,(void *) arg);
	if(rc){
		cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
	}
	//pthread_attr_destroy(&attr);
	//rc = pthread_join(thread1,NULL);
	//pthread_attr_init(&attr1);
	rc=pthread_create(&thread2,NULL,displayQueue,(void *)arg);
	if(rc){
		cout << "Error:unable to create thread,"<< rc << endl;
		exit(-1);
	}
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_exit(NULL);
}
int main()
{
	thready_call();	
	return 0;
}

