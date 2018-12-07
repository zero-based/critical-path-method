#include "Task.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

void findCP(float maxEF, int numberOfTasks, Task *arrTasks);
int getNextTask(float maxEF, int numberOfTasks, Task *arrTasks, Task &x);

void main()
{
	SetConsoleTitle(L"CPM - Critical Path Method: C++ Sample Application");
	cout << "\n CPM - Critical Path Method C++ Sample Application\n";
	cout << " This program demonstrates the Critical Path Method's algorithm.\n";
	cout << "------------------------------------------------------------------\n\n";

	int numberOfTasks;
	do{
		cout << setw(25) << "Enter Number of Tasks: ";
		cin >> numberOfTasks;
		if (numberOfTasks <= 2){
			cout << "  Number of tasks should be greater than 2!";
			Beep(1200, 800);
			Sleep(1500);
			cout << '\r' << "                                                        " << '\r';
		}
	} while (numberOfTasks <= 2);
	cin.ignore();


	// Input
	Task *arrTasks = new Task[numberOfTasks];
	for (int i = 0; i < numberOfTasks; i++) {
		cout << "\n\n";
		cout << setw(23) << "Task #" << i + 1 << "\n\n";
		arrTasks[i].inputData(numberOfTasks);
	}

	// Calculate Early Start and Eatly Finish
	for (int i = 0; i < numberOfTasks; i++) {
		arrTasks[i].calculateEarlyStartAndFinish(numberOfTasks, arrTasks);
	}

	// Get Maximum Early Finish of all Tasks
	float maxEF = 0;
	for (int i = 0; i < numberOfTasks; i++)
	{
		if (maxEF < arrTasks[i].EF)
			maxEF = arrTasks[i].EF;
	}

	// Assign Maximum Early Finish to the Late Finish Terminal Tasks
	// and calculate their Late Start
	for (int i = 0; i < numberOfTasks; i++)
	{
		arrTasks[i].initTerminalTasks(maxEF, numberOfTasks, arrTasks);
	}

	// Calculate Late Start and Eatly Finish
	for (int i = 0; i < numberOfTasks; i++)
	{
		arrTasks[i].calculateLateStartAndFinish(maxEF, numberOfTasks, arrTasks);
	}

	cout << "\n\n------------------------------------------------------------------\n\n";

	//Output
	cout << "\nTotal Duration: " << maxEF << "\n";

	cout << "\n\n\nCritical Path(s):\n\n";
	findCP(maxEF, numberOfTasks, arrTasks);

	cout << "\n\n\nTasks' Early/Late Starts and Finishes: \n\n";
	for (int i = 0; i < numberOfTasks; i++) {
		arrTasks[i].printStartAndFinish();
	}

	cout << "\n\n\n";
	delete[]arrTasks;
	system("pause");
}



void findCP(float maxEF, int numberOfTasks, Task *arrTasks)
{
	string CP = "- ";
	for (int i = 0; i < numberOfTasks; i++)
	{
		if (arrTasks[i].ES == 0 && arrTasks[i].LS - arrTasks[i].ES == 0 && arrTasks[i].LF - arrTasks[i].EF == 0)
		{
			while (true)
			{
				CP += arrTasks[i].name + " "; //add first one to Critical Path

				int index = 0;
				index = getNextTask(maxEF, numberOfTasks, arrTasks, arrTasks[i]); //get index of next of first one

				if (index != -1)
				{
					CP += arrTasks[index].name + " "; //add next of first one to Critical Path

					while (true)
					{
						index = getNextTask(maxEF, numberOfTasks, arrTasks, arrTasks[index]); //get index of next of next

						if (index != -1)
							CP += arrTasks[index].name + " "; //add next of next to Critical Path
						else
							break;
					}

					cout << CP << endl;
					CP = "- ";
				}
				else
					break;
			}
		}
	}
}

int getNextTask(float maxEF, int numberOfTasks, Task *arrTasks, Task &x)
{
	/// returns index of next task in the array of Tasks if found
	/// or return -1 if not
	/// N.B.: Task must have v1 = v2 = 0

	for (int i = 0; i < numberOfTasks; i++)
	{
		for (int depNum = 0; depNum < arrTasks[i].numberOfDependencies; depNum++)
		{
			if (arrTasks[i].Dependencies[depNum] == x.name)
			{
				if (arrTasks[i].LS - arrTasks[i].ES == 0 && arrTasks[i].LF - arrTasks[i].EF == 0)
				{
					if (arrTasks[i].LF != maxEF)
						arrTasks[i].Dependencies[depNum] = "";
					return i;
				}
			}
		}
	}
	return -1;
}