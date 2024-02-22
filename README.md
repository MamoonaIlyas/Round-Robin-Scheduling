Round Robin Scheduling Algorithm Implementation:

This C++ program demonstrates the Round Robin scheduling algorithm, which is a widely used CPU scheduling algorithm in operating systems. Round Robin is a preemptive algorithm where each process is assigned a fixed time unit, known as a time quantum, and executed in a circular manner.

Key Features:

1. Process Structure: Defines a structure `Process` representing a process with attributes such as ID, burst time, and arrival time.

2. Average Waiting Time Calculation: Computes the average waiting time for processes using the Round Robin algorithm with and without arrival times.

3. Average Turnaround Time Calculation: Calculates the average turnaround time for processes considering Round Robin scheduling with and without arrival times.

4. Gantt Chart Display: Generates and displays Gantt charts illustrating the execution sequence of processes both with and without arrival times.

Functions:

- `avgWaitingTime()`: Computes the average waiting time for processes without considering arrival times.
- `findTurnAroundTime()`: Calculates the turnaround time for each process.
- `findAvgTime()`: Computes the average waiting time and average turnaround time for processes.
- `displayGanttChartWithoutArrivalTime()`: Displays the Gantt chart representing the execution sequence of processes without arrival times.
- `displayGanttChartWithArrivalTime()`: Displays the Gantt chart with arrival times.
- `roundRobinWithoutArrivalTime()`: Implements the Round Robin scheduling algorithm without considering arrival times.
- `roundRobinWithArrivalTime()`: Implements the Round Robin algorithm considering arrival times.

Usage:

- User inputs the number of processes, burst time, arrival time, and time quantum.
- The program calculates and displays the average waiting time and average turnaround time for both scenarios: with and without arrival times.
- Gantt charts are displayed to visualize the execution sequence of processes.

This implementation provides insights into the Round Robin scheduling algorithm and can be used for educational purposes or as a reference for implementing scheduling algorithms in operating systems.
