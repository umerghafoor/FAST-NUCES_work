#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <queue>
#include <mutex>


constexpr int NUM_DATA = 4;

// Shared resources
std::queue<int> stage1Queue, stage2Queue;
std::mutex mtxStage1, mtxStage2;
std::vector<int> output;

// Semaphores
std::counting_semaphore<1> semStage1(1); // Controls access to Stage 1
std::counting_semaphore<1> semStage2(0); // Waits until Stage 1 produces
std::counting_semaphore<1> semStage3(0); // Waits until Stage 2 processes

// Stage 1: Reads data
void stage1(const std::vector<int>& input) {
    for (int data : input) {
        semStage1.acquire();
        {
            std::lock_guard<std::mutex> lock(mtxStage1);
            stage1Queue.push(data);
            std::cout << "Stage 1: Read " << data << "\n";
        }
        semStage2.release();
    }
}

// Stage 2: Processes data
void stage2() {
    for (int i = 0; i < NUM_DATA; ++i) {
        semStage2.acquire();
        int data;
        {
            std::lock_guard<std::mutex> lock(mtxStage1);
            data = stage1Queue.front();
            stage1Queue.pop();
        }
        data *= 2;
        {
            std::lock_guard<std::mutex> lock(mtxStage2);
            stage2Queue.push(data);
            std::cout << "Stage 2: Processed to " << data << "\n";
        }
        semStage3.release();
    }
}

// Stage 3: Writes data
void stage3() {
    for (int i = 0; i < NUM_DATA; ++i) {
        semStage3.acquire();
        int data;
        {
            std::lock_guard<std::mutex> lock(mtxStage2);
            data = stage2Queue.front();
            stage2Queue.pop();
        }
        {
            std::lock_guard<std::mutex> lock(mtxStage1); // To safely update the output
            output.push_back(data);
            std::cout << "Stage 3: Wrote " << data << "\n";
        }
        semStage1.release();
    }
}

int main() {
    std::vector<int> input = {1, 2, 3, 4};

    // Launch threads for each stage
    std::thread t1(stage1, std::cref(input));
    std::thread t2(stage2);
    std::thread t3(stage3);

    // Wait for threads to finish
    t1.join();
    t2.join();
    t3.join();

    // Print the output array
    std::cout << "Final Output: ";
    for (int num : output) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
