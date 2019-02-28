#include<iostream>
#include<thread>
#include<string>
#include <mutex>  
#include <chrono>
#include <fstream>
#include <condition_variable> // std::condition_variable
using namespace std;
condition_variable cv;
mutex rw_mtx ; /* semaphore common to both reader & writer */
mutex mtx ; /* semaphore for reading (reader lock) */
int read_count = 0; /* track number of readers in CS */
int l0ck(){
    /*
        Use th lock to signal other 
        thread to stop as the area ahead is being utilised
    */
}
int unlock(){
    /*
    Use th unlock to signal other 
    thread to stop as the area ahead is being utilised
    */
}
string str="";
void writer(int x){
    do{
        cout<<"Writer "+to_string(x)+" waiting\n";
        rw_mtx.lock();
        cout << "Writer " +to_string(x)+" to write\n";
        int res = 1;              
        cout<<"Write to file using writer "+to_string(x)+" yes(1) and no(0)\t";
        cin>>res;
        if(res){
            //open file and copy its content to string variable str
            ifstream infile; 
            infile.open("q1.txt"); 
            infile >> str;               
            cout<<"write(1) or append(0)\t"; 
            cin>>res;
            string input;
            cout<<"Input to be writen\n";
            cin>>input;
            if(res){
                str = input;
            }
            else{
                str+=input;
            }
            //open file and copy str content to it
            ofstream myfile;
            myfile.open ("q1.txt");
            myfile << str;
            myfile.close();
        }
        rw_mtx.unlock();
    }
    while(true);
}
void reader(int z){
    do{ 
        cout<<"Reader "+to_string(z)+" waiting\n";
        mtx.lock();
        /* first update read_count atomically */
        read_count++;
        if (read_count == 1) {
            rw_mtx.lock();            
            /* ensure no writer can enter */
        }
        mtx.unlock();
        /* allow other readers to access */
        /* reading is performed */

        //open file and copy its content to string variable str
        ifstream infile; 
        infile.open("q1.txt"); 
        infile >> str; 
        cout<<"Reader "+to_string(z)+" and the file has\t"+str+"\n";
        mtx.lock();
        read_count--;
        if (read_count == 0) 
            rw_mtx.unlock();
            /* allow writers after
                last reader has left the CS */
        mtx.unlock();
    }
    while(true);    
}
int main(){
    thread w1(writer,1);
    thread r1(reader,1);
    thread w2(writer,2);
    thread w3(writer,3);
    thread r2(reader,2);
    w1.join();
    w2.join();
    r1.join();
    w3.join();
    r2.join();

    return 0;
}
