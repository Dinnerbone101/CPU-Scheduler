#include <bits/stdc++.h>
#include "scheduler.h"
using namespace std;

void fcfs(vector<Process>& processes) {

    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;
    vector<int> gantt;
    vector<int> timeMarks;

    

    timeMarks.push_back(time);

    for (auto &p : processes) {
        if (time < p.arrivalTime) {
            gantt.push_back(0); // idle
            time = p.arrivalTime;
            timeMarks.push_back(time);
        }

        gantt.push_back(p.pid);

        time += p.burstTime;
        timeMarks.push_back(time);

        p.completionTime = time;
        p.turnaroundTime = time - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }

    printGanttChart(gantt, timeMarks);
    printTable(processes);
}



 void sjf(vector<Process>& processes) {
    int n = processes.size();

    // Sort by arrival time first (tie → burst time)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        if (a.arrivalTime == b.arrivalTime)
            return a.burstTime < b.burstTime;
        return a.arrivalTime < b.arrivalTime;
    });

    vector<bool> done(n, false);
    int completed = 0;
    int time = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;

        // Find shortest job among arrived processes
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= time) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        // If no process has arrived yet → move time forward
        if (idx == -1) {
            time++;
            continue;
        }

        // Execute selected process
        time += processes[idx].burstTime;

        processes[idx].completionTime = time;
        processes[idx].turnaroundTime =
        processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime =
        processes[idx].turnaroundTime - processes[idx].burstTime;

        done[idx] = true;
        completed++;
    }
}


void roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();

    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    queue<int> q; // stores indices of processes
    int time = 0;
    int i = 0; // pointer for processes
    int completed = 0;

    // Push first arriving processes
    while (i < n && processes[i].arrivalTime <= time) {
        q.push(i);
        i++;
    }

    if (q.empty()) {
        time = processes[0].arrivalTime;
        q.push(0);
        i = 1;
    }

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        int execTime = min(quantum, processes[idx].remainingTime);

        // Execute process
        processes[idx].remainingTime -= execTime;
        time += execTime;

        // Add newly arrived processes during execution
        while (i < n && processes[i].arrivalTime <= time) {
            q.push(i);
            i++;
        }

        // If process still has work → push back
        if (processes[idx].remainingTime > 0) {
            q.push(idx);
        } else {
            // Process finished
            processes[idx].completionTime = time;
            processes[idx].turnaroundTime =time - processes[idx].arrivalTime;
            processes[idx].waitingTime =processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }

        // If queue empty but processes remain → jump time
        if (q.empty() && i < n) {
            time = processes[i].arrivalTime;
            q.push(i);
            i++;
        }
    }
}


void printTable(const vector<Process>& processes) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto p : processes) {
        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\n";
    }
}


void printGanttChart(const vector<int>& gantt, const vector<int>& timeMarks) {
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < gantt.size(); i++) {
        if (gantt[i] == 0)
            cout << "| Idle ";
        else
            cout << "| P" << gantt[i] << " ";
    }
    cout << "|\n";

    for (int t : timeMarks) {
        cout << t << "\t";
    }
    cout << endl;
}