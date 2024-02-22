#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
};

void avgWaitingTime(int n, int burst_time[], int waiting_time[], int quantum, int arrival_time[]) {
    int remainingBurstTime[n];
    for (int i = 0; i < n; i++)
        remainingBurstTime[i] = burst_time[i];
    int t = 0;

    while (1) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0 && arrival_time[i] <= t) {
                done = false;
                if (remainingBurstTime[i] > quantum) {
                    t += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    t = t + remainingBurstTime[i];
                    waiting_time[i] = t - burst_time[i] - arrival_time[i];
                    remainingBurstTime[i] = 0;
                }
            }
        }

        if (done == true)
            break;
    }
}

void findTurnAroundTime(int n, int burst_time[], int wait_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++)
        turnaround_time[i] = burst_time[i] + wait_time[i];
}

void findAvgTime(int n, int burst_time[], int quantum, int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], totalWaitingTime = 0, totalTurnaroundTime = 0;

    avgWaitingTime(n, burst_time, waiting_time, quantum, arrival_time);
    findTurnAroundTime(n, burst_time, waiting_time, turnaround_time);

    cout << "Processes\tArrival time\tBurst time\tWaiting time\tTurnaround time\n";

    for (int i = 0; i < n; i++) {
        totalWaitingTime = totalWaitingTime + waiting_time[i];
        totalTurnaroundTime = totalTurnaroundTime + turnaround_time[i];
        cout << " " << i + 1 << "\t\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    cout << "Average waiting time = " << (float)totalWaitingTime / (float)n << endl;
    cout << "Average turnaround time = " << (float)totalTurnaroundTime / (float)n << endl;
}

// Function to display Gantt Chart Without Arrival Time
void displayGanttChartWithoutArrivalTime(const list<int>& queue, const vector<int>& completionTimes) {
    cout << endl;
    cout << "Gantt Chart Without Arrival Time:" << endl;
    cout << string(100, '-') << endl;
    cout << "|";

    auto queueIt = queue.begin();
    auto completionIt = completionTimes.begin();

    while (queueIt != queue.end()) {
        cout << "  P" << *queueIt << " (" << *completionIt << ")  |";
        ++queueIt;
        ++completionIt;
    }

    cout << "\n" << string(100, '-') << endl;
}

// Function to display Gantt Chart With Arrival Time
void displayGanttChartWithArrivalTime(const list<pair<int, int>>& queueWithArrival, const vector<int>& completionTimes) {
    cout << endl;
    cout << "Gantt Chart With Arrival Time:" << endl;
    cout << string(100, '-') << endl;
    cout << "|";

    for (const auto& process : queueWithArrival) {
        cout << "  P" << process.first << " (" << process.second << ")  |";
    }

    cout << "\n" << string(100, '-') << endl;

    cout << "Completion Time:";
    for (int i = 0; i < completionTimes.size(); ++i) {
        cout << setw(5) << completionTimes[i];
    }
    cout << endl;
}

// Function to perform Round Robin scheduling without arrival time
void roundRobinWithoutArrivalTime(list<Process>& processes, int quantum, vector<int>& completionTimes, double& avgWaitingTime, double& avgTurnaroundTime) {
    int n = processes.size();
    list<int> queue;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    while (!processes.empty()) {
        auto it = processes.begin();
        while (it != processes.end()) {
            if (it->burstTime > 0) {
                queue.push_back(it->id);
                int executedTime = min(quantum, it->burstTime);
                currentTime += executedTime;
                totalWaitingTime += currentTime - it->arrivalTime - executedTime;
                totalTurnaroundTime += currentTime - it->arrivalTime;
                it->burstTime -= executedTime;

                completionTimes.push_back(currentTime);

                if (it->burstTime == 0) {
                    it = processes.erase(it);
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }

    avgWaitingTime = static_cast<double>(totalWaitingTime) / n;
    avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;

    displayGanttChartWithoutArrivalTime(queue, completionTimes);
}

// Function to perform Round Robin scheduling with arrival time
void roundRobinWithArrivalTime(list<Process>& processes, int quantum, vector<int>& completionTimes, double& avgWaitingTime, double& avgTurnaroundTime) {
    int n = processes.size();
    list<pair<int, int>> queueWithArrival;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    while (!processes.empty()) {
        auto it = processes.begin();
        while (it != processes.end()) {
            if (it->arrivalTime <= currentTime && it->burstTime > 0) {
                queueWithArrival.push_back({it->id, currentTime});
                int executedTime = min(quantum, it->burstTime);
                currentTime += executedTime;
                totalWaitingTime += currentTime - it->arrivalTime - executedTime;
                totalTurnaroundTime += currentTime - it->arrivalTime;
                it->burstTime -= executedTime;

                completionTimes.push_back(currentTime);

                if (it->burstTime == 0) {
                    it = processes.erase(it);
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }

    avgWaitingTime = static_cast<double>(totalWaitingTime) / n;
    avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;

    displayGanttChartWithArrivalTime(queueWithArrival, completionTimes);
}

int main() {
    cout<<"\n *************** ROUND ROBIN SCHEDULING ALGORITHM **************** \n"<<endl;
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    list<Process> processesWithoutArrival;
    list<Process> processesWithArrival;

    cout << "Enter burst time and arrival time for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        int burst, arrival;
        cout << "Process " << i + 1 << ": " << endl;
        cout << "Arrival Time : ";
        cin >> arrival;
        cout << "Burst Time: ";
        cin >> burst;
        processesWithoutArrival.push_back({i + 1, burst, arrival});
        processesWithArrival.push_back({i + 1, burst, arrival});
    }

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    double avgWaitingTimeWithoutArrival = 0.0;
    double avgTurnaroundTimeWithoutArrival = 0.0;
    vector<int> completionTimesWithoutArrival;

    double avgWaitingTimeWithArrival = 0.0;
    double avgTurnaroundTimeWithArrival = 0.0;
    vector<int> completionTimesWithArrival;

    // Sort processes with arrival times
    processesWithArrival.sort([](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    roundRobinWithoutArrivalTime(processesWithoutArrival, quantum, completionTimesWithoutArrival, avgWaitingTimeWithoutArrival, avgTurnaroundTimeWithoutArrival);

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time Without Arrival Time: " << avgWaitingTimeWithoutArrival << endl;
    cout << "Average Turnaround Time Without Arrival Time: " << avgTurnaroundTimeWithoutArrival << endl;

    roundRobinWithArrivalTime(processesWithArrival, quantum, completionTimesWithArrival, avgWaitingTimeWithArrival, avgTurnaroundTimeWithArrival);

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time With Arrival Time: " << avgWaitingTimeWithArrival << endl;
    cout << "Average Turnaround Time With Arrival Time: " << avgTurnaroundTimeWithArrival << endl;
    cout<<endl;
    return 0;
}
