

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
using namespace std;

// Process structure
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function declarations
void fcfs(vector<Process>& processes);
void sjf(vector<Process>& processes);
void roundRobin(vector<Process>& processes, int timeQuantum);

// Utility functions
void printTable(const vector<Process>& processes);
void printGanttChart(const vector<int>& gantt, const vector<int>& timeMarks);

#endif