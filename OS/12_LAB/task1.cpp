#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

struct Task {
    int taskId;
    int taskPriority;
    int resourceNeed;
    int resourcesGranted;
};

struct PriorityCompare {
    bool operator()(Task const &t1, Task const &t2) {
        return t1.taskPriority < t2.taskPriority;
    }
};

class ResourceAllocator {
private:
    int maxResources;
    int freeResources;
    priority_queue<Task, vector<Task>, PriorityCompare> taskQueue;
    mutex allocatorMutex;
    condition_variable allocatorCV;

public:
    ResourceAllocator(int resources) : maxResources(resources), freeResources(resources) {}

    void request(Task t) {
        unique_lock<mutex> lock(allocatorMutex);
        cout << "Task " << t.taskId << " (Priority: " << t.taskPriority
             << ") needs " << t.resourceNeed << " resources.\n";
        taskQueue.push(t);

        allocatorCV.wait(lock, [&]() {
            Task top = taskQueue.top();
            return (top.taskId == t.taskId && t.resourceNeed <= freeResources);
        });

        freeResources -= t.resourceNeed;
        cout << "Task " << t.taskId << " granted " << t.resourceNeed
             << " resources. Remaining: " << freeResources << "\n";
        taskQueue.pop();
    }

    void release(int taskId, int resources) {
        unique_lock<mutex> lock(allocatorMutex);
        freeResources += resources;
        cout << "Task " << taskId << " released " << resources
             << " resources. Remaining: " << freeResources << "\n";
        allocatorCV.notify_all();
    }
};

void executeTask(ResourceAllocator &allocator, Task t) {
    allocator.request(t);
    this_thread::sleep_for(chrono::seconds(2));
    allocator.release(t.taskId, t.resourceNeed);
}

int main() {
    int resources = 5;
    ResourceAllocator allocator(resources);

    vector<Task> tasks = {
        {1, 3, 3, 0},
        {2, 1, 2, 0},
        {3, 2, 4, 0}
    };

    vector<thread> taskThreads;
    for (auto &t : tasks) {
        taskThreads.emplace_back(thread(executeTask, ref(allocator), t));
    }

    for (auto &th : taskThreads) {
        th.join();
    }

    return 0;
}