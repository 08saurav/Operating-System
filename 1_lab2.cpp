#include<stdio.h>//for normal io and perrror
#include<iostream>
#include<sys/types.h>//for data type pid_t
#include<sys/wait.h>//for wait system call
#include<unistd.h>//for fork(),exit() system call
#include<stdlib.h>//for abort()

using namespace std;

typedef long long int ll;
ll n1,n2,n;

int main(int argc,char *argv[])
{
	int p[2];
	pipe(p);
	ll ans;
	pid_t pid;
	pid = fork();
	if((pid<0)){
		perror("fork");
	}
	else if(pid==0){
		printf("I am a Child Process\n");
		n=atoi(argv[1]);
		//close(p[0]);
		//close(1);
		cin>>n;
		n1=0,n2=1;
		for(ll i=0;i<n;i++)
		{
			if(i<=1)
				ans =i;
			else{
				ans=n1+n2;
				n1=n2;
				n2=ans;
			}
		}
		if(n==1)
			ans=1;
		close(p[0]);
		close(1);
		dup(p[1]);
		write(1,&ans,sizeof(ans));
		return 0;
	}
	else{
		cout << "I am a Parent Process" << endl;
		wait(NULL);
		cout << "Child Terminated";
		close(0);
		close(p[1]);
		dup(p[0]);
		unsigned long long a;
		int n=read(p[0],&a,sizeof(a));
		cout << a << " " << n << endl;
	}
	return 0;
}


