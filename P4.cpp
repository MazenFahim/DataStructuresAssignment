#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>


using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool isAdded;                       // to check if the process has been added to the ready queue or not
};

void round_robin(vector<Process>& processes, int n, int time_quantum)
{
    queue<int> cpu_queue;
    int current_time = 0;
    int completed_processes = 0;          // to keep track of the number of completed processes

    cout << "Queue Updates: " << endl;

    while (completed_processes < n)
    {

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && !processes[i].isAdded)
            {
                cpu_queue.push(i);
                processes[i].isAdded = true; 
                cout << "[ P " << processes[i].id << " ]" << endl;
            }
        }
       
       if (cpu_queue.empty())
        {
            cout << "[ Empty ]" << endl;
            current_time++;
            continue;                 // If CPU queue is empty we move to the next time sec. and check again for arriving processes
        } 
        
       
        int element = cpu_queue.front();          // get the element at the front to execute it and then pop it from the queue whatever it finish or not 
        cpu_queue.pop();

        int ExecutionTime = 0 ;    // it is the time of the current process execution
        while(processes[element].remaining_time > 0 && ExecutionTime < time_quantum){
            processes[element].remaining_time--;
            current_time++;
            ExecutionTime++;
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrival_time <= current_time && !processes[i].isAdded)   // if there is a process that arrives during the execution of the current process we add it to the queue
                {
                    cpu_queue.push(i);
                    processes[i].isAdded = true; 
                }
            }
        }

        if( processes[element].remaining_time > 0)           // if the current process isn't finished yet we add it again at the end of the cpu queue 
        {
            cpu_queue.push(element);
        }
        else        // required calculations if the process is finished
        {
            processes[element].completion_time = current_time; 
            processes[element].turnaround_time = processes[element].completion_time - processes[element].arrival_time;
            processes[element].waiting_time = processes[element].turnaround_time - processes[element].burst_time;
            completed_processes++;
        }

        if (!cpu_queue.empty())
        {
            queue<int> temp_queue = cpu_queue;
            cout << "[ ";
            while (!temp_queue.empty())
            {
                cout << "P " << processes[temp_queue.front()].id;
                temp_queue.pop();
                if (!temp_queue.empty())
                    cout << ", ";
            }
            cout << " ]" << endl;
        }
    }
    cout << "[ Empty ]" << endl;     // at the end of execution of all processess in the cpu queue and in vector 
}


int main()
{
    int time_quantum, n;
    cout << "Time Quantum: ";
    cin >> time_quantum;
    cout << "Number of Processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Arrival Time, Needed Time P" << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].isAdded = false; 
    }

    round_robin(processes, n, time_quantum);

    cout << "Process  Completion Time  Turnaround Time  Waiting Time" << endl;
    float total_wait_time = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].id << "\t   " << processes[i].completion_time << "\t\t   " << processes[i].turnaround_time << "\t\t   " << processes[i].waiting_time << endl;
        total_wait_time += processes[i].waiting_time;
    }
    cout << "Average Waiting Time: " << (float)total_wait_time / n << endl;
    return 0;
}