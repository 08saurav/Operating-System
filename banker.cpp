#include<iostream>

using namespace std;

int allocated[100][100],maxx[100][100],available[1000],need[100][100],finish[1000]={0},order[1000];


int safety(int i,int m){
	for(int j=0;j<m;j++)
		if(need[i][j]>available[j])
			return 0;
	return 1;
}

int main(){
	int n,m,i,j,count=0,k=0,flag=0,d=0;
	// m resources n process 
	cout<<"Enter number of process and resources\n";
	cin>>n>>m;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			cin>>allocated[i][j];

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>maxx[i][j];
			need[i][j]=maxx[i][j]-allocated[i][j];
		}
	}
	for(i=0;i<m;i++)
		cin>>available[i];
	i=0;
	while(count<n){
		flag=0;
		for(i=0;i<n;i++){
			if(finish[i]==0 && safety(i,m)){
				flag=1;
				finish[i]=1;
				count++;
				for(j=0;j<m;j++)
					available[j]+=allocated[i][j];
				order[k]=i;
				k++;
			}
		}
		if(flag==0){
			cout<<"DeadLock!\n";
			d=1;
			break;
		}
	}
	if(d==0){
		for(i=0;i<n;i++)
			cout<<"P"<<order[i]<<'\n';
	}
	return 0;
}
