#include "Task.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;


Task::Task()
{
}

void Task::inputData(int numberOfTasks)
{
	cout << setw(25) << "Task's Name: ";
	getline(cin, name);
	transform(name.begin(), name.end(), name.begin(), toupper);

	cout << setw(25) << "Duration: ";
	cin >> duration;

	do{
		cout << setw(25) << "Dependencies number: ";
		cin >> numberOfDependencies;
		if (numberOfDependencies > numberOfTasks - 1){
			cout << "    Dependencies should be less than number of Tasks!";
			Beep(1200, 800);
			Sleep(1500);
			cout << '\r' << "                                                        " << '\r';
		}
	} while (numberOfDependencies > numberOfTasks - 1);

	cin.ignore();
	Dependencies = new string[numberOfDependencies];

	for (int i = 0; i < numberOfDependencies; i++)
	{
		if (numberOfDependencies == 1)
			cout << setw(25) << "Dependency's Name: ";
		else if (i < 9)
			cout << setw(15) << "Dependency #" << i + 1 << "'s Name: ";
		else if (i >= 9)
			cout << setw(14) << "Dependency #" << i + 1 << "'s Name: ";

		getline(cin, Dependencies[i]);
		transform(Dependencies[i].begin(), Dependencies[i].end(), Dependencies[i].begin(), toupper);
	}

}

void Task::calculateEarlyStartAndFinish(int numberOfTasks, Task *arrTasks)
{
	if (ES == -1)
	{
		if (numberOfDependencies == 0)
		{
			ES = 0;
		}
		else
		{
			float maxES = 0;

			for (int depNum = 0; depNum < numberOfDependencies; depNum++)
			{
				for (int taskNum = 0; taskNum < numberOfTasks; taskNum++)
				{
					if (Dependencies[depNum] == arrTasks[taskNum].name)
					{
						if (arrTasks[taskNum].EF == -1)
						{
							arrTasks[taskNum].calculateEarlyStartAndFinish(numberOfTasks, arrTasks);
						}
						if (maxES < arrTasks[taskNum].EF)
						{
							maxES = arrTasks[taskNum].EF;
						}
					}
				}
			}

			ES = maxES;
		}

		EF = ES + duration;
	}
}

void Task::initTerminalTasks(float maxEF, int numberOfTasks, Task *arrTasks){

	bool isFound = false;

	for (int taskNum = 0; taskNum < numberOfTasks; taskNum++)
	{
		for (int depNum = 0; depNum < arrTasks[taskNum].numberOfDependencies; depNum++)
		{
			if (name == arrTasks[taskNum].Dependencies[depNum])
			{
				isFound = true;
			}
		}
	}

	if (!isFound)
	{
		LF = maxEF;
		LS = maxEF - duration;
	}
}

void Task::calculateLateStartAndFinish(float maxEF, int numberOfTasks, Task *arrTasks)
{
	float minLS = maxEF;

	for (int taskNum = 0; taskNum < numberOfTasks; taskNum++)
	{
		for (int depNum = 0; depNum <arrTasks[taskNum].numberOfDependencies; depNum++)
		{
			if (name == arrTasks[taskNum].Dependencies[depNum])
			{
				if (arrTasks[taskNum].LS == -1)
				{
					arrTasks[taskNum].calculateLateStartAndFinish(maxEF, numberOfTasks, arrTasks);
				}

				if (minLS > arrTasks[taskNum].LS)
				{
					minLS = arrTasks[taskNum].LS;
				}
			}
		}

		LF = minLS;
	}

	LS = LF - duration;
}



void Task::printStartAndFinish()
{
	cout << name << ":\n";
	cout << "ES: " << setw(6) << left << ES << "EF: " << EF << endl
		<< "LS: " << setw(6) << left << LS << "LF: " << LF << endl << endl;
}

Task::~Task()
{
	delete[]Dependencies;
}
