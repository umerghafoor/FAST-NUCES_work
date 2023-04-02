struct task{
int id;
int dur;
int s_Time; //start time of each task
int e_Time; //end time of each task
int* dep; /*list of predecessors of this task - To simplify we assume that a
highernumber task will depend on a lower number task e.g. T2 can depend on T1
OR T4 can depend on T2 but the opposite is not true.*/
};
class Scheduler
{
private:
	task* tasks;
	int numTasks;
public:
	// provide definitions of following functions...
	Scheduler();// default constructor
	Scheduler(task* ts, int n);//initialized the project with n tasks
	//you have to implement the following functions
	// think about the parameters required and return type of the following functions
	void setTaskDuration(int);//change task duration of all tasks
	void set_nth_TaskDuration(int,int);//change duration of a specific task
	void printTaskDependencyList(int);//print dependencies of a specific task
	void completionTime();//print completion time of the project
	void printCriticalTasks();/*returns array of critical tasks and displays them –
	sum of their duration should be equal to project completion time*/
	~Scheduler();//destructor
}