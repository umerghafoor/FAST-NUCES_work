#include "Scheduler.h"
#include <iostream>
using namespace std;

Scheduler::Scheduler() 
{
	tasks = nullptr;
	numTasks = 0;
}
Scheduler::Scheduler(task* ts, int n)
{
    numTasks = n;
    tasks = new task[n];
    for (int i = 0; i < n; i++)
    {
        tasks[i] = ts[i];
    }
}
void Scheduler::setTaskDuration(int duration) 
{
    for (int i = 0; i < numTasks; i++) 
    {
        tasks[i].dur = duration;
    }
}
void Scheduler::set_nth_TaskDuration(int taskIndex, int duration)
{
    tasks[taskIndex].dur = duration;
}
void Scheduler::printTaskDependencyList(int taskIndex)
{

}
void Scheduler::completionTime()
{

}
void Scheduler::printCriticalTasks()
{

}
Scheduler::~Scheduler()
{
    cout << "distructor" << endl;
}