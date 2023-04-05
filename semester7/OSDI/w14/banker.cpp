#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>
#define PROCESS_N 5
#define RESOURCE_N 4
using namespace std;

typedef struct {
    string name;
    bool done;
    int allocation[RESOURCE_N];
    int max_request[RESOURCE_N];
    int remain_need[RESOURCE_N];
} Process;

class Resource {
public:
    void print_available_resource();
    void print_process_state();
    bool Safe();
    bool Request(int req_process, int* req_resource);
    int available_resource[RESOURCE_N];
    int available_resource_bk[RESOURCE_N];
    vector<Process> process;
    vector<Process> process_bk;
    vector<string> safe_seq;
};

void Resource::print_available_resource()
{
    printf("Available resources: (");
    for (int i = 0; i < RESOURCE_N; i++) {
        printf(" %d ", this->available_resource[i]);
    }
    printf(")\n");
}

void Resource::print_process_state()
{
    printf("\tResource Allocation | MAx Request | Remaining Needs\n");
    for (auto it = this->process.begin(); it != this->process.end(); it++) {
        printf("Process %s:\t", it->name.c_str());
        for (int i = 0; i < RESOURCE_N; i++) {
            printf(" %d ", it->allocation[i]);
        }
        printf("\t|\t");
        for (int i = 0; i < RESOURCE_N; i++) {
            printf(" %d ", it->max_request[i]);
        }
        printf("\t|\t");
        for (int i = 0; i < RESOURCE_N; i++) {
            printf(" %d ", it->remain_need[i]);
        }
        printf("\n");
    }
}

bool Resource::Safe()
{
    this->safe_seq.clear();
    bool can_run, have_run;
    while (!this->process.empty()) {
        have_run = false;
        for (auto it = this->process.begin(); it != this->process.end(); it++) {
            can_run = true;
            if (!it->done) {
                for (int i = 0; i < RESOURCE_N; i++) {
                    if (this->available_resource[i] < it->remain_need[i]) {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) {
                    have_run = true;
                    this->safe_seq.push_back(it->name);
                    for (int i = 0; i < RESOURCE_N; i++) {
                        this->available_resource[i] += it->allocation[i];
                    }
                    this->process.erase(it);
                    break;
                }
            }
        }
        if (!have_run) {
            printf("Unsafe!\n");
            return false;
        }
    }
    printf("Safe!\nSafeSequence: ");
    for (auto it : this->safe_seq) {
        printf("%s ", it.c_str());
    }
    printf("\n");
    return true;
}

bool Resource::Request(int req_process, int* req_resource)
{
    for (int i = 0; i < RESOURCE_N; i++) {
        if (req_resource[i] > this->process.at(req_process).remain_need[i]) {
            printf("Exceed Remaining Needs\n");
            return false;
        }
        if (req_resource[i] > this->available_resource[i]) {
            printf("Exceed Available Resource\n");
            return false;
        }
    }
    for (int i = 0; i < RESOURCE_N; i++) {
        this->available_resource[i] -= req_resource[i];
        this->process.at(req_process).allocation[i] += req_resource[i];
        this->process.at(req_process).remain_need[i] -= req_resource[i];
    }
    return true;
}

int main(int argc, char* argv[])
{
    int available_resource;
    int allocation[RESOURCE_N];
    int max_request[RESOURCE_N];
    int remain_need[RESOURCE_N];
    string name;
    Resource resource;

    for (int i = 0; i < RESOURCE_N; i++) {
        cin >> available_resource;
        resource.available_resource[i] = available_resource;
        resource.available_resource_bk[i] = available_resource;
    }
    for (int i = 0; i < PROCESS_N; i++) {
        cin >> name;
        for (int j = 0; j < RESOURCE_N; j++) {
            cin >> allocation[j];
        }
        for (int j = 0; j < RESOURCE_N; j++) {
            cin >> max_request[j];
        }
        for (int j = 0; j < RESOURCE_N; j++) {
            cin >> remain_need[j];
        }
        resource.process.push_back({ name });
        resource.process.back().done = false;
        for (int j = 0; j < RESOURCE_N; j++) {
            resource.process.back().allocation[j] = allocation[j];
            resource.process.back().max_request[j] = max_request[j];
            resource.process.back().remain_need[j] = remain_need[j];
        }
    }
    resource.process_bk.assign(
        resource.process.begin(), resource.process.end());

    // print data
    printf("===Banker's algorithm starts!\n");
    resource.print_available_resource();
    resource.print_process_state();
    // print data

    printf("===Safety algorithm starts!\n");
    if (resource.Safe()) {
        int req_process;
        int req_resource[RESOURCE_N];
        string buf;
        copy(begin(resource.available_resource_bk),
            end(resource.available_resource_bk),
            begin(resource.available_resource));
        resource.process.assign(
            resource.process_bk.begin(), resource.process_bk.end());
        printf("Resource-Request algorithm starts!\n");
        while (true) {
            printf("Request! Enter process no: \n");
            cin >> req_process;
            for (int i = 0; i < RESOURCE_N; i++) {
                printf("Enter request resource #%d = \n", i);
                cin >> req_resource[i];
            }
            if (resource.Request(req_process, req_resource)) {
                resource.print_available_resource();
                resource.print_process_state();
                copy(begin(resource.available_resource),
                    end(resource.available_resource),
                    begin(resource.available_resource_bk));
                resource.process_bk.assign(
                    resource.process.begin(), resource.process.end());
                if (resource.Safe()) {
                    copy(begin(resource.available_resource_bk),
                        end(resource.available_resource_bk),
                        begin(resource.available_resource));
                    resource.process.assign(
                        resource.process_bk.begin(), resource.process_bk.end());
                }
            }
            printf("Continue the Banker's algorithm? (Yes=y or Y)\n");
            cin >> buf;
            if (buf == "y" || buf == "Y") {
                continue;
            } else {
                break;
            }
        }
        printf("Bye! End of Banker's algorithm!\n");
    };

    return 0;
}
