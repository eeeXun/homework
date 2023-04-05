#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define MODEL "SJF"
using namespace std;

typedef struct {
    int arrival_time;
    int cpu_burst;
    int priority;
    string name;
} Data;

class Simulator {
public:
    Simulator();
    void equeue(string name, int arrival_time, int cpu_burst, int priority);
    void run();

private:
    void sort_burst();
    void sort_arrive();
    vector<Data> queue;
    int queue_size;
    int clock;
    float waiting;
};

Simulator::Simulator()
{
    this->clock = 0;
    this->waiting = 0;
}

void Simulator::equeue(
    string name, int arrival_time, int cpu_burst, int priority)
{
    this->queue.push_back({ arrival_time, cpu_burst, priority, name });
}

bool compare_by_burst(const Data& a, const Data& b)
{
    return a.cpu_burst < b.cpu_burst;
}

void Simulator::sort_burst()
{
    sort(this->queue.begin(), this->queue.end(), compare_by_burst);
}

bool compare_by_arrive(const Data& a, const Data& b)
{
    return a.arrival_time < b.arrival_time;
}

void Simulator::sort_arrive()
{
    sort(this->queue.begin(), this->queue.end(), compare_by_arrive);
}

void Simulator::run()
{
    bool process_selected;
    this->queue_size = this->queue.size();

    this->sort_arrive();
    if (strcmp(MODEL, "SJF") == 0)
        this->sort_burst();

    if (strcmp(MODEL, "FCFS") == 0 || strcmp(MODEL, "SJF") == 0) {
        while (!this->queue.empty()) {
            process_selected = false;
            for (auto it = this->queue.begin(); it != this->queue.end(); it++) {
                if (this->clock >= it->arrival_time) {
                    process_selected = true;
                    printf("clock %d:\t%s, arrival_time = %d, cpu_burst = %d, "
                           "priority = %d, completion_time = %d\n",
                        this->clock, it->name.c_str(), it->arrival_time,
                        it->cpu_burst, it->priority,
                        this->clock + it->cpu_burst);
                    this->clock += it->cpu_burst;
                    this->waiting
                        += this->clock - it->arrival_time - it->cpu_burst;
                    this->queue.erase(it);
                    break;
                }
            }
            if (!process_selected)
                this->clock++;
        }
    }
    printf(
        "The average waiting time = %.2f\n", this->waiting / this->queue_size);
}

int main(int argc, char* argv[])
{
    Simulator simulator;
    string name;
    int arrival_time;
    int cpu_burst;
    int priority;

    printf("Input workload (sorted by arrival time):\n");
    printf("Process Name\t->\tArrival Time\t->\tCPU Burst\t->\tPriority\n");

    while (cin >> name >> arrival_time >> cpu_burst >> priority) {
        simulator.equeue(name, arrival_time, cpu_burst, priority);
    }

    printf("==========Process scheduling by " MODEL "\n");
    simulator.run();

    return 0;
}
