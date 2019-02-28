

#include <pthread.h> 
#include<bits/stdc++.h>
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#define MAX 10 
using namespace std;
int main() 
{ 
int fd[2], i = 0; 
pipe(fd); 
pid_t pid = fork();
//pid_t pid1= fork();
/*if(pid > 0 ) { 
	wait(NULL);
	pid_t pid1= fork();
	close(0);
	close(fd[1]); 
	dup(fd[0]); 
	int arr[10]; 
	int n = read(fd[0], arr, sizeof(arr)); 
	for ( i = 1;i < n/4; i++){
		if(arr[0]==0)
			break;
		arr[0]--;
		printf("%d ", arr[i]); 
	}*/
 if( pid == 0 ) { 
	//pid_t pid1= fork();
	int arr[10],n,size;
		cout<<"enter size of queue\n";
	cin>>size;
	cout<<"enter number of elements\n";
	cin>>n;
	if(n==0)
		cout<<"queue is empty\n";
	arr[0]=n;
	for(i=1;i<=n;i++)
		cin>>arr[i];
	if(size==n)
		cout<<"queue is full\n";
	if(size>n){
		cout "only first " << n << " elements will be shown" << endl;
		arr[0]=size;
	}
	close(fd[0]); 
	close(1);	 
	dup(fd[1]); 
	write(1, arr, sizeof(arr)); 
}
else{
	wait(NULL);
	pid_t pid1 = fork();
	if(pid1==0){
		wait(NULL);
        close(0);
        close(fd[1]);
        dup(fd[0]);
        int arr[10];
        int total;
        //cout<<"number of elements to print";
//        cin>>total;
        int n = read(fd[0], arr, sizeof(arr));
	//cout << n;
        for ( i = 1;i < n/4; i++){
                if(arr[0]==0)
                        break;
                arr[0]--;
                printf("%d ", arr[i]);
}
}
}
}

