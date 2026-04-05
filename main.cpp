#include <bits/stdc++.h>
#include "scheduler.h"
using namespace std;


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;

        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrivalTime;

        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;

        processes[i].remainingTime = processes[i].burstTime;
    }

    int choice;

    cout << "\nChoose Scheduling Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(processes);
            break;

        case 2:
            sjf(processes);
            break;

        case 3: {
            int tq;
            cout << "Enter Time Quantum: ";
            cin >> tq;
            roundRobin(processes, tq);
            break;
        }

        default:
            cout << "Invalid choice\n";
    }

    return 0;
}