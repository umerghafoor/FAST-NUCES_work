#include "Scheduler.h"
#include <iostream>
using namespace std;

int main()
{
	int numberOftasks;

	int numDep;
	cout << "\tEnter Data" << endl;
	cout << "Enter Total Tasks : ";cin >> numberOftasks;
	task* tasks = new task[numberOftasks];
	for (int i = 0; i < numberOftasks; i++)
	{
		cout << endl;
		cout << "\tEnter task " << i + 1 << " details" << endl;
		tasks[i].id = i + 1;
		cout << "Enter task duration       : ";
		cin >> tasks[i].dur;
		cout << "Enter task start time     : ";
		cin >> tasks[i].s_Time;
		tasks[i].e_Time = tasks[i].s_Time + tasks[i].dur;
		tasks[i].dep = new int[i];
		cout << "Enter no. of dependencies : ";
		cin >> numDep;
		tasks[i].num_dep = numDep;
		if (numDep != 0) 
		{
			cout << "Enter task dependencies" << endl;
			for (int j = 0; j < numDep; j++)
			{
				cout << "Enter Dependency   : ";cin >> tasks[i].dep[j];
			}
		}
	}
	

	Scheduler project(tasks, numberOftasks);
	system("pause");
	system("cls");
	int dur, id;
	int choice = 1;
	while (choice != 0)
	{
		cout << "Select an option:" << endl;
		cout << "1 Change task duration of all tasks" << endl;
		cout << "2 Change duration of a specific task" << endl;
		cout << "3 Print dependencies of a specific task" << endl;
		cout << "4 Print completion time of the project" << endl;
		cout << "5 Print critical tasks" << endl;
		cout << "0 Exit" << endl;
		cout << "Enter choice : ";cin >> choice;
		cout << "==================================================" << endl;
		switch (choice)
		{
		case 1:
			project.setTaskDuration();
			break;
		case 2:
			cout << "\tChange duration of a specific task" << endl;
			cout << "Enter ID of Task              : ";cin >> id;
			cout << "Enter new duration for task "<<id<<" : ";cin >> dur;
			project.set_nth_TaskDuration(id, dur);
			break;
		case 3:
			cout << "\tPrint dependencies of a specific task" << endl;
			cout << "Enter task ID : ";
			cin >> id;
			project.printTaskDependencyList(id);
			break;
		case 4:
			cout << "\tPrint completion time of the project" << endl;
			project.completionTime();
			break;
		case 5:
			cout << "\tPrint critical tasks" << endl;
			project.printCriticalTasks();
			break;
		}
		system("pause");
		system("cls");
	}
}