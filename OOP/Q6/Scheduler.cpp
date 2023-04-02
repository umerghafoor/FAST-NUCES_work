#include "Scheduler.h"
#include <iostream>
#include <vector>
using namespace std;

Scheduler::Scheduler()
{
    ts = nullptr;
    noOfTasks = 0;
}
Scheduler::Scheduler(task* ts, int n) 
{
    this->ts = new task[n];
    this->noOfTasks = n;
    for (int i = 0; i < n; i++) 
    {
        this->ts[i] = ts[i];
    }
}
void Scheduler::setTaskDuration() 
{
    int dur;
    for (int i = 0; i < noOfTasks; i++) 
    {
        cout << "Enter new duration for task "<<i+1<<" : ";
        cin >> dur;
        ts[i].dur = dur;
        ts[i].e_Time = ts[i].s_Time + ts[i].dur;
    }
}
void Scheduler::set_nth_TaskDuration(int task_id, int dur) 
{
    if (task_id < 1 || task_id > noOfTasks)
    {
        cout << "Invalid task ID" << endl;
        return;
    }
    ts[task_id - 1].dur = dur;
    ts[task_id - 1].e_Time = ts[task_id - 1].s_Time + ts[task_id - 1].dur;
}
void Scheduler::printTaskDependencyList(int task_id)
{
    int* dep;
    int num_dep;
    cout << "Dependencies of task " << task_id << endl;
    for (int i = 0; i < noOfTasks; i++)
    {
        if (ts[i].id == task_id)
        {
            dep = ts[i].dep;
            for (int j = 0; j < ts[i].num_dep; j++)
            {
                cout << "Task " << dep[j] << endl;
            }
            return;
        }
    }
    cout << "Task " << task_id << " not found." << endl;
}
void Scheduler::completionTime() 
{
    int maxTime = 0;
    int endTime = 0;
    int earliestStartTime;
    int depIndex;
    int depEndTime;
    for (int i = 0; i < noOfTasks; i++) 
    {
        earliestStartTime = 0;
        for (int j = 0; j < ts[i].num_dep; j++)
        {
            depIndex = ts[i].dep[j] - 1;
            depEndTime = ts[depIndex].e_Time;
            if (depEndTime > earliestStartTime) 
            {
                earliestStartTime = depEndTime;
            }
        }

        ts[i].s_Time = earliestStartTime;
        ts[i].e_Time = earliestStartTime + ts[i].dur;

        endTime = ts[i].e_Time;
        if (endTime > maxTime) 
        {
            maxTime = endTime;
        }
    }

    cout << "Project completion time : " << maxTime << endl;
}

task* Scheduler::printCriticalTasks()
{
    int dependentId;
    int dependentSTime;
    int currentETime;
    int slackTime;

    for (int i = 0; i < noOfTasks; i++)
    {
        for (int j = 0; j < ts[i].num_dep; j++)
        {
            dependentId = ts[i].dep[j];
            for (int k = 0; k < noOfTasks; k++)
            {
                if (ts[k].id == dependentId)
                {
                    
                    slackTime = ts[i].s_Time -ts[i].e_Time; + ts[i].dur;
                    cout << ts[i].slackTime << ' ' << slackTime << endl;
                    if (ts[i].slackTime > slackTime)
                    {
                        ts[i].slackTime = slackTime;
                    }
                    break;
                }
            }
        }
    }

    int numCriticalTasks = 0;
    for (int i = 0; i < noOfTasks; i++)
    {
    //    cout << ts[i].slackTime << endl;
        if (ts[i].slackTime == 0)
        {
            numCriticalTasks++;
        }
    }

    task* criticalTasks = new task[numCriticalTasks];

    int j = 0;
    for (int i = 0; i < noOfTasks; i++)
    {
        if (ts[i].slackTime == 0)
        {
            criticalTasks[j] = ts[i];
            j++;
        }
    }
    int sum = 0;
    cout << "No. of Critical tasks : " << numCriticalTasks << endl;
    cout << "Sum of Critical tasks : ";
    for (int i = 0; i < numCriticalTasks; i++)
    {
        
        sum += criticalTasks[i].dur;
    }
    sum += (ts[0].dur + ts[0].s_Time);
    cout<<sum << endl;
    return criticalTasks;
}


Scheduler::~Scheduler() 
{
    delete[] ts;
}