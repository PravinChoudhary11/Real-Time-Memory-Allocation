#ifndef TASK_SIMULATOR_H
#define TASK_SIMULATOR_H

#include "FirstFitAllocator.h"
#include <queue>
#include <iostream>
#include <windows.h> // For Sleep function

// Structure representing a real-time task
struct RealTimeTask {
    int id;
    int memoryRequired;
    int deadline;  // For future scheduling use

    RealTimeTask(int id, int mem, int dl) : id(id), memoryRequired(mem), deadline(dl) {}
};

// Simulator for processing tasks with memory allocation requests
class TaskSimulator {
private:
    FirstFitAllocator& allocator;
    std::queue<RealTimeTask> tasks;

public:
    TaskSimulator(FirstFitAllocator& alloc) : allocator(alloc) {}

    // Add a task to the simulation queue
    void addTask(const RealTimeTask& task) {
        tasks.push(task);
    }

    // Process tasks: allocate memory, simulate task execution, then deallocate memory
    void processTasks() {
        while (!tasks.empty()) {
            RealTimeTask task = tasks.front();
            tasks.pop();
            std::cout << "Processing Task " << task.id 
                      << " requiring " << task.memoryRequired << " bytes\n";
            
            MemoryBlock* block = allocator.allocate(task.memoryRequired);
            if(block) {
                std::cout << "Task " << task.id << " allocated block at address " 
                          << block->start << " of size " << block->size << "\n";
                
                // After allocating, display the memory map
                std::cout << "Memory after allocation:\n";
                allocator.displayMemoryMap();
                
                // Simulate task execution delay with Windows Sleep (milliseconds)
                Sleep(500);
                
                // Deallocate the memory block
                allocator.deallocate(block);
                std::cout << "Task " << task.id << " deallocated memory\n";
                
                // After deallocating, display the memory map
                std::cout << "Memory after deallocation:\n";
                allocator.displayMemoryMap();
            } else {
                std::cout << "Task " << task.id << " failed to allocate memory!\n";
            }
        }
    }
};

#endif // TASK_SIMULATOR_H