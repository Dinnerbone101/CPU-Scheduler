# CPU Scheduling Simulator

This project is a CPU Scheduling Simulator built in C++ that demonstrates how different scheduling algorithms work in an operating system.

## Features

- FCFS (First Come First Serve)
- SJF (Shortest Job First - Non Preemptive)
- Round Robin Scheduling
- Gantt Chart Visualization
- Calculates:
  - Completion Time
  - Waiting Time
  - Turnaround Time

## Tech Stack

- C++
- STL (Vectors, Queue, Algorithm)

## How to Run

1. Compile the code:
   g++ main.cpp scheduler.cpp -o scheduler

2. Run the program:
   ./scheduler

## Sample Input

Number of processes: 3

PID   AT   BT  
1     0    5  
2     1    3  
3     2    1  

## Sample Output

Gantt Chart:
| P1 | P2 | P3 |
0    5    9    12

PID  AT  BT  CT  TAT  WT  
1    0   5   5   5    0  
2    1   3   9   8    5  
3    2   1   12  10   9  

## Future Improvements

- Preemptive SJF (SRTF)
- Priority Scheduling
- GUI-based visualization
