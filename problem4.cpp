#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//تقريبا فاضل الفانكشن بتاع النيو و شوية تعديلات على الاوتبوت 
class ProcessDetails{
    public:
    int id;
    int need;
    int arrival;
    int remaining;
    
};

bool arriveFirst(ProcessDetails a, ProcessDetails b) {
    return a.arrival < b.arrival;
}


void printQueue(queue<int> q) {
    if (q.empty()) {
        cout<< "[Empty]" << endl;
    }else{
        cout<< "[ ";
        queue<int> temp = q;
        while(!temp.empty()){
            cout << "P" << temp.front() << " ";
            temp.pop();
        }
        cout << "]" << endl;
    }
}

bool checkNew(vector<ProcessDetails>que){

}


int main(){

int process,done=0,clock=0,timeQuantum,currentTime=0,waitingTime;
cin >> process;
cin >> timeQuantum;

queue < int > que;
vector<ProcessDetails> pro(process);


for(int i=0; i<process; i++){
   cin>> pro[i].id >> pro[i].need >> pro[i].arrival ;
}
sort(pro.begin(),pro.end(),arriveFirst);


while (done<process){

    if(currentTime==pro[1].arrival){
        que.push(pro[1].id);
        printQueue(que);}
    int timeNeeded= pro[1].need + timeQuantum; 
    if (timeNeeded<= timeQuantum){
        que.pop();
        pro[1].remaining =0;
        currentTime= pro[1].need ;
    }
    else{
        if (timeNeeded > timeQuantum){

        }
    }
    
}
}
