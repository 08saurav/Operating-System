#include<iostream>
#include<cstdio>
#include<vector>
#include <algorithm>

using namespace std;
int ttime = 1;
class process{
    public:
    int pid;
    int burst_time;
    int arrival_time;
    int ready_queue;
    int chance;
    int time_quantum;
    int waiting_time;
    int tat;
    process(int pd,int bt,int at,int rq){
        pid = pd;
        burst_time = bt;
        arrival_time = at;
        ready_queue = rq;
        chance  =2;
        time_quantum = rq+2;
        waiting_time = 0;
    }
    void change(int rq){
        chance = 2;
        ready_queue = rq;
        time_quantum = rq+2;
    }
    void print(){
        cout<<"Process ID: ";
        cout<<pid<<'\n';
        // cout<<"Arrival Time: \t";
        // cout<<arrival_time<<'\n';
        // cout<<"Burst Time: \t";
        // cout<<burst_time<<'\n';
        // cout<<"Ready Queue: \t";
        // cout<<ready_queue<<'\n';
    }
    void printt(){
        cout<<"The process that finished\n";
        cout<<"Process ID: ";
        cout<<pid<<'\n';
        cout<<"Waiting Time: ";
        cout<<ttime - burst_time -arrival_time<<'\n';
        cout<<"Turn around Time: ";
        cout<<ttime - arrival_time<<'\n';
        
    }
};

vector<process> q[5];
vector<process> v;
void push(process d,int rq){
   q[rq].insert(q[rq].end(),d);
}
void pop(int rq){
    q[rq].erase(q[rq].begin());
}

process front(int rq){
    return *q[rq].begin();
}

bool myfunction (process i,process j) { 
    return (i.arrival_time<j.arrival_time); 
}
int round_robin(int rq){
    sort (q[rq].begin(), q[rq].end(), myfunction);
    while(!q[rq].empty()){
        process p = front(rq);
        pop(rq);
        if(p.chance == 0){            
            p.change(rq+1);
            push(p,rq+1);
            cout<<"The process that moves down to queue "<<rq+2<<'\t';
            p.print();
            
        }
        else{
            p.chance-=1;
            p.burst_time=p.burst_time-p.time_quantum; 
            if(p.burst_time > 0){
                cout<<"The process that is executing is from queue "<<rq+1<<'\t';
                ttime+=p.time_quantum;
                //p.waiting_time =ttime-p.quantum_time-p.arrival_time<< endl;
		//cout << "waiting time " << p.waiting_time << endl;
		p.waiting_time=+1;
                p.print();
                push(p,rq);
            }
            else{
                p.printt();
            }
        }
        cout<<"Time of system\t"<<ttime<<'\n';
        bool ad = false;
        for(vector<process>::iterator it = v.begin();it != v.end();++it){
            if(it->arrival_time <= ttime){
                int rq = it->ready_queue;
                process p = *it;
                cout<<"New process arrived";
                cout<<"Sending to Queue "<<rq<<" process "<<p.pid<<'\n';
                push(p,rq);
                ad =true;
                it = v.erase(it);
                if(it == v.end())
                    break;
            }                   
        }
        if(ad == true){
            return 1;
        }    
    }
    return 0;
}

int fcfs(int rq){
    sort (q[rq].begin(), q[rq].end(), myfunction);
    while(!q[rq].empty()){
        process p = front(rq);
        pop(rq);        
        p.burst_time=p.burst_time-p.time_quantum; 
        if(p.burst_time > 0){
            cout<<"The process that is executing is from queue "<<1+rq<<'\t';
            p.print();
            push(p,rq);
        }
        else{
            p.printt();
    	}
        bool ad = false;
        for(vector<process>::iterator it = v.begin();it != v.end();++it){
            if(it->arrival_time <= ttime){
                int rq = it->ready_queue;
                process p = *it;
                cout<<"Sending to Queue "<<rq<<" process "<<p.pid<<'\n';
                push(p,rq); 
                ad =true;
            }                   
        }
        if(ad){
            return 1;
        }       
    }
    return 0;
}
int main(){
    int n;
    cout<<"Total no. of process :\t";
    cin>>n;
    for (int i =0; i < n; i++){
        int bt,at,rq,pd;
        cout<<"Process ID: \t";
        cin>>pd;
        cout<<"Arrival Time: \t";
        cin>>at;
        cout<<"Burst Time: \t";
        cin>>bt;
        cout<<"Ready Queue: \t";
        cin>>rq;
        process p(pd,bt,at,rq-1);
        if(at == 1){
            push(p,rq-1);
        }
        else{
            v.insert(v.end(),p);
        }    
        //push(p,rq-1);

    }
    sort (v.begin(), v.end(), myfunction);
    for(int i =0;i < 5;i++){
        int k; 
        if(i == 4 ){
            k = fcfs(4);    
        }
        else{
            k = round_robin(i);
        }
        if(k == 1){
            i = -1;
        }
    }
    cout<<"The process that are left in queue \n";
    for (int i = 0; i < 5 ; i++){
        while(!q[i].empty()){
            process p = front(i);
            cout<<"Ready Queue"<<i+1<<'\t'<<"Process ID:"<<p.pid<<'\n' ;
            pop(i);
        }
    }
}
