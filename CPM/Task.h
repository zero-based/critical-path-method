#pragma once
#include <string>
using namespace std;

class Task
{
public:
	string name;
	float duration;
	int numberOfDependencies = 0;
	string *Dependencies;
	float ES = -1, EF = -1, LS = -1, LF = -1;

public:
	Task();
	void inputData(int numberOfTasks);
	void calculateEarlyStartAndFinish(int numberOFtask, Task *arrTasks);
	void initTerminalTasks(float maxEF, int numberOfTasks, Task *arrTasks);
	void calculateLateStartAndFinish(float maxEF, int numberOfTasks, Task *arrTasks);
	void printStartAndFinish();
	~Task();
};

