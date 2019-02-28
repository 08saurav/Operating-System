#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;
//readyqueue =0,device_queue=1;
int ttime = 1;
class process{
	public:
		int pid;
		int b_time,b1_time;
		int a_time;
		int r_queue;
		int d_queue;
		int q_time;
		int w_time;
		int io_time,io1_time;
		int a1_time;
		int priority;
		process(int pd,int bt,int at,int p,int io)
		{
			pid = pd;
			b_time=bt;
			a_time=at;
			a1_time=at;
			r_queue=0;
			w_time=0;
			q_time=4;
			priority=p;
			io_time = io;
			io1_time=io;
			b1_time=bt;
			cout << a_time << endl;
		}
		void change(int rq)
		{
			r_queue=rq;
		}

		void print(){
			cout << "Process ID:  ";
			cout << pid<<'\n';
		}
		void printt(){
			cout<<"The process that finished\n";
			cout<<"Process ID: ";
			cout<<pid<<'\n';
			cout << "arival_time:  " << a_time << endl;
			cout << "total time:  " << ttime<< endl;
			cout<<"Waiting Time: ";
			cout<<ttime - b1_time -a_time-io1_time<<'\n';
			cout<<"Turn around Time: ";
			cout<<ttime - a_time<<'\n';

		}
};
vector<process>q[2];
vector<process>v;
void push(process d,int rq){
	q[rq].insert(q[rq].end(),d);
}
void pop(int rq){
	q[rq].erase(q[rq].begin());
}
process front(int rq){
	return *q[rq].begin();
}
bool myfunction(process i,process j){
	return (i.a1_time<j.a1_time);
}
bool pri(process i,process j){
	if(ttime-1==0){
		if(i.a_time<j.a_time)
			return true;
		if(i.a_time>j.a_time)
			return false;
		if(i.a_time==j.a_time)
		{
			if(i.priority>j.priority)
				return true;
			else 
				return false;
		}
	}
	else
	{
		if(i.a_time<=ttime-1 && j.a_time<=ttime-1)
		{
			if(i.priority>j.priority)
				return true;
			else
				return false;
		}
		else if(i.a_time>ttime-1 && j.a_time<=ttime-1)
			return false;
		else if(i.a_time<=ttime && j.a_time>ttime-1)
			return true;
		else if(i.a_time>ttime-1 && j.a_time>ttime-1)
		{
			if(i.a_time<j.a_time)
				return true;
			if(i.a_time>j.a_time)
				return false;
			if(i.a_time==j.a_time){
				if(i.priority>j.priority)
					return true;
				else if(i.priority<i.priority)
					return false;
			}
		}
	}
	//return (i.priority>j.priority);
}
bool burst(process i,process j){
	if(i.a1_time>j.a1_time)
		return false;
	if(i.a1_time<j.a1_time)
		return true;
	if(i.a1_time==j.a1_time)
	{
		if(i.b_time<=j.b_time)
			return true;
		else
			return false;
	}
}
bool io(process i,process j){

	if(i.a1_time<j.a1_time)
		return true;
	if(i.a1_time>j.a1_time)
		return false;
	if(i.a1_time==j.a1_time)
	{
		if(i.io_time<=j.io_time)
			return true;
		else
			return false;
	}
}
bool srcmpcpu(process i,process j){
	if(ttime-1>i.a_time && ttime-1>j.a_time){
		if(i.a_time<j.a_time)
			return true;
		else if(i.a_time>j.a_time)
			return false;
		else if(i.a_time==j.a_time)
		{
			if(i.b_time<=j.b_time)
				return true;
			else
				return false;
		}
	}
	else if(ttime-1<i.a_time && ttime-1>j.a_time)
		return true;
	else if(ttime-1>i.a_time && ttime-1<j.a_time)
		return false;
	else if(ttime-1 <= i.a_time && ttime-1<= j.a_time)
	{
		if(i.b_time<=j.b_time)
			return true;
		else 
			return false;
	}
}
bool srcmpio(process i,process j){
        if(ttime-1>i.a_time && ttime-1>j.a_time){
                if(i.a_time<j.a_time)
                        return true;
                else if(i.a_time>j.a_time)
                        return false;
                else if(i.a_time==j.a_time)
                {
                        if(i.io_time<=j.io_time)
                                return true;
                        else
                                return false;
                }
        }
        else if(ttime-1<i.a_time && ttime-1>j.a_time)
                return true;
        else if(ttime-1>i.a_time && ttime-1<j.a_time)
                return false;
        else if(ttime-1 <= i.a_time && ttime-1<= j.io_time)
        {
                if(i.io_time<=j.io_time)
                        return true;
                else
                        return false;
        }
}

bool a[1000]={false};
int rr(){
	//sort(q[rq].begin(),q[rq].end(),myfuntion);
	while(!q[0].empty())
	{
		int rq=0;
		sort(q[rq].begin(),q[rq].end(),burst);
		process p = front(rq);
		pop(rq);
		if(a[p.pid]==false)
		{
			ttime=ttime+p.a_time;
			a[p.pid]=true;
		}
		if(p.b_time>p.q_time)
		{
			p.b_time=p.b_time-p.q_time;
			ttime=ttime+p.q_time;
			p.a1_time=ttime;
			push(p,rq);
			p.print();
			cout << "response of ur process request with response time:   " <<p.q_time << endl;
			//cout << "burst time" << p.b_time << endl;
		}
		else if(p.b_time<p.q_time)
		{
			//p.b_time=0;
			ttime+=p.b_time;
			if(p.io_time>0 && p.b_time!=0){
				//push(p,1);
				p.b_time=0;
				cout << "process moves to device queue having process id:   "<<p.pid << endl;
				p.a1_time=ttime;
				push(p,1);
			}
			else{
				p.b_time=0;
				p.printt();
				cout<<"Process finished having process id:   "<< p.pid << endl;
			}
		}
	}
	while(!q[1].empty())
	{
		int rq=1;
		sort(q[rq].begin(),q[rq].end(),io);
		process p=front(rq);
		if(a[p.pid]==false)
		{
			a[p.pid]==true;
			ttime=ttime+p.a_time;
		}
		pop(rq);
		if(p.io_time>p.q_time)
		{
			p.io_time=p.io_time-p.q_time;
			ttime=ttime+p.q_time;
			p.a1_time=ttime;
			push(p,rq);
			p.print();
			cout << "response of ur process request with response io time:   " <<p.q_time << endl;

		}
		else
		{
			//p.io_time=0;
			ttime+=p.io_time;
			p.io_time=0;
			p.printt();
			cout <<"Process finished all work of io and cpu having process id: "<<p.pid<< endl;
		}
	}

}
void fcfs()
{
	while(!q[0].empty()){
		//if(a[p.pid])
		int rq=0;
		sort(q[rq].begin(),q[rq].end(),burst);
		process p=front(rq);
		if(a[p.pid]==false){
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		pop(rq);
		ttime+=p.b_time;
		p.b_time=0;
		if(p.io_time>0){
			push(p,rq+1);
			p.a1_time=ttime;
			p.print();
			cout << "Process moves down to device queue having  Processs ID:  " << p.pid << endl; 
		}
		else
		{
			p.printt();
			cout <<"Process finished all works of io and cpu having Process ID:   "<<p.pid<< endl;
		}
	}
	while(!q[1].empty()){
		int rq=1;
		sort(q[rq].begin(),q[rq].end(),io);
		process p=front(rq);
		if(a[p.pid]==false)
		{
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		pop(rq);
		ttime+=p.io_time;
		p.io_time=0;
		p.printt();
		cout << "Process finshed all works of io and cpu having Process ID:   "<<p.pid<< endl;
	}
}
void srtf()
{
	while(!q[0].empty()){
		sort(q[0].begin(),q[0].end(),srcmpcpu);
		process p = front(0);
		if(a[p.pid]==false){
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		ttime++;
		p.b_time--;
		pop(0);
		if(p.b_time==0 && p.io_time>0){
			push(p,1);
			p.a1_time=ttime;
			p.print();
			cout << "process moves down to device queue having Process ID:  "<<p.pid << endl;
		}
		else if(p.b_time>0){
			push(p,0);
			cout<<"process checking for next sortest remainig time process  and now executing process having pid:  "<<p.pid<<endl;
		}
		else{
			p.printt();
			cout << "Process finished all works of io and cpu having Process ID: " << p.pid << endl;
		}
	}
	while(!q[1].empty()){
		sort(q[1].begin(),q[1].end(),srcmpio);
		process p = front(1);
		if(a[p.pid]==false){
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		ttime++;
		p.io_time--;
		pop(1);
		if(p.io_time>0){
			push(p,1);
			cout<<"process checking for next sortest remainig time process and now executing process having pid:  "<< p.pid<< endl;
		}
		else{
			p.printt();
			cout << "Process finished all works of io and cpu having Process ID: " << p.pid << endl;
		}
	}
	
}
void priority()//no-preemption
{
	while(!q[0].empty()){
		int rq=0;
		sort(q[rq].begin(),q[rq].end(),pri);
		process p=front(rq);
		if(a[p.pid]==false){
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		pop(rq);
		ttime+=p.b_time;
		p.b_time=0;
		if(p.io_time>0){
			push(p,rq+1);
			p.a1_time=ttime;
			p.print();
			cout << "Process moves down to device queue having  Processs ID:  " << p.pid << endl; 
		}
		else
		{
			p.printt();
			cout <<"Process finished all works of io and cpu having Process ID:   "<<p.pid<< endl;
		}
	}
	while(!q[1].empty()){
		int rq=1;
		sort(q[rq].begin(),q[rq].end(),pri);
		process p=front(rq);
		if(a[p.pid]==false){
			a[p.pid]=true;
			ttime=ttime+p.a_time;
		}
		pop(rq);
		ttime+=p.io_time;
		p.io_time=0;
		p.printt();
		cout << "Process finshed all works of io and cpu having Process ID:   "<<p.pid<< endl;
	}
}
void prem_priority()
{

}
int main()
{
	int n;
	cout << "Enter the no. of processes you wanna to enter:  ";
	cin >> n;
	for(int i=0;i<n;i++){
		int at,bt,pd,p1,io;
		cout<<"Process ID:  ";
		cin >> pd;
		cout << "arrival time:  ";
		cin >> at;
		cout <<"CPU Burst time:  ";
		cin >> bt;
		cout << "io Burst time:  ";
		cin >> io;
		cout <<"Priority of a process:  ";
		cin >> p1;
		process p(pd,bt,at,p1,io);
		push(p,0);
	}
	cout << "Choose which algorithm you want to Run;  "<<endl;
	cout << "Enter 1 for fcfs,2 for round_robin,3 for srtf,4 priority scheduling(no premption),5 for priority scheduling(premption):  "<< endl;
	int k;
	cin >> k;
	if(k==1)
		fcfs();
	else if(k==2)
		rr();
	else if(k==3)
		srtf();
	else if(k==4)
		priority();
	//else if(k==5)
	//	non_prem_priority();
	cout << "Done" << endl;
	return 0;
}
