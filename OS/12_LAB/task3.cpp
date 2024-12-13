#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

const int NUM_PHILOSOPHERS = 5;
const int BUS_SEATS = 3;
const int BUS_TIMEOUT = 5000; // Timeout in milliseconds

mutex forks[NUM_PHILOSOPHERS];
mutex busMutex;
condition_variable busCondition;

queue<int> busQueue;
bool busDeparted = false;

void philosopher(int id) {
    while (true) {
        // Thinking
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::milliseconds(1000)); // Thinking for 1 second

        // Attempt to eat
        int leftFork = id;
        int rightFork = (id + 1) % NUM_PHILOSOPHERS;

        unique_lock<mutex> leftLock(forks[leftFork], defer_lock);
        unique_lock<mutex> rightLock(forks[rightFork], defer_lock);

        lock(leftLock, rightLock); // Lock both forks
        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::milliseconds(1000)); // Eating for 1 second
        cout << "Philosopher " << id << " has finished eating.\n";

        // Finished eating, release forks and try to board the bus
        leftLock.unlock();
        rightLock.unlock();

        // Wait for a seat on the bus
        {
            unique_lock<mutex> busLock(busMutex);
            if (busQueue.size() < BUS_SEATS) {
                busQueue.push(id);
                cout << "Philosopher " << id << " has boarded the bus.\n";

                // Notify the bus if all seats are filled
                if (busQueue.size() == BUS_SEATS) {
                    busCondition.notify_one();
                }
            } else {
                cout << "Philosopher " << id << " is waiting for the next bus.\n";
                busCondition.wait(busLock, [&] { return busDeparted; });
            }
        }

        // Simulate bus ride
        if (busDeparted) {
            this_thread::sleep_for(chrono::milliseconds(2000)); // Riding the bus
        }
    }
}

void bus() {
    while (true) {
        unique_lock<mutex> busLock(busMutex);

        // Wait until seats are filled or timeout
        if (busCondition.wait_for(busLock, chrono::milliseconds(BUS_TIMEOUT), [] { return busQueue.size() == BUS_SEATS; })) {
            cout << "Bus is departing with " << busQueue.size() << " philosophers.\n";
        } else {
            cout << "Bus is departing due to timeout with " << busQueue.size() << " philosophers.\n";
        }

        // Simulate bus ride
        this_thread::sleep_for(chrono::milliseconds(2000));

        // Empty the bus
        while (!busQueue.empty()) {
            cout << "Philosopher " << busQueue.front() << " has exited the bus.\n";
            busQueue.pop();
        }

        busDeparted = true;
        busCondition.notify_all(); // Notify waiting philosophers
        busDeparted = false; // Reset for the next bus
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];
    thread busThread(bus);

    // Start philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = thread(philosopher, i);
    }

    // Join philosopher threads (though they run infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    // Join the bus thread (also runs infinitely)
    busThread.join();

    return 0;
}