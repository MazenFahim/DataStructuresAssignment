#include <iostream>
#include <queue>
#include <algorithm>

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
    bool isJoined = false; // Flag to check if the process has been added to the ready queue or not
};

void round_robin(Process processes[], int n, int time_quantum)
{
    queue<int> ready_queue;
    int current_time = 0;
    int completed_processes = 0;

    cout << "\nQueue Updates: " << endl;

    // add processes that have arrived at time 0 to the ready queue
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time <= current_time)
        {
            ready_queue.push(i);
            processes[i].isJoined = true;
        }
    }

    while (completed_processes < n)
    {
        if (ready_queue.empty())
        {
            cout << "[ Empty ]" << endl;
            current_time++;
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrival_time <= current_time && !processes[i].isJoined)
                {
                    ready_queue.push(i);
                    processes[i].isJoined = true;
                }
            }
            continue;
        }

        queue<int> temp_queue = ready_queue;
        cout << "[ ";
        while (!temp_queue.empty())
        {
            cout << "P" << processes[temp_queue.front()].id;
            temp_queue.pop();
            if (!temp_queue.empty())
                cout << ", ";
        }
        cout << " ]" << endl;
    }
    cout << "[ Empty ]" << endl;
}

int main()
{
    int time_quantum, n;
    cout << "Time Quantum: ";
    cin >> time_quantum;
    cout << "Number of Processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Arrival Time, Needed Time P" << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].isJoined = false;
    }

    round_robin(processes, n, time_quantum);

    cout << "\nProcess  Completion Time  Turnaround Time  Waiting Time\n";
    float total_wait_time = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].id << "\t " << processes[i].completion_time << "\t\t " << processes[i].turnaround_time << "\t\t " << processes[i].waiting_time << endl;
        total_wait_time += processes[i].waiting_time;
    }
    cout << "\nAverage Waiting Time: " << (float)total_wait_time / n << endl;
    return 0;
}