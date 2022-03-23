//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: pq.cpp
//
// Description: interactive command with PriorityQueue class
//
// Acknowledgement: (1) Doctor Chang's Notes
//		    (2) Class demo programs
//
//---------------------------------------------------------------------


#include "PriorityQueue.cpp"
#include <iostream>
#include <string>

using namespace std;
template <typename T>
void commandPrompt(T);
int main()
{
	int dataType;
	cout<<" Specify what data type to store in priority queue:\n";
	cout<<"\t1) int\n";
	cout<<"\t2) float\n";
	cout<<"\t3) double\n";
	cout<<"\t4) string\n";
	cout<<"\t5) bool\n";
	cout<<">";
	cin>>dataType;
	
	while(dataType<1 || dataType >5)
	{
		cout<<"\nPlease enter a valid choice.\n";
		cout<<">";
		cin>>dataType;
	}
	
	if (dataType==1)
		{
			int value;
			commandPrompt(value);
		}
		else if (dataType==2)
		{
			float value;
			commandPrompt(value);
		}
		else if (dataType==3)
		{
			double value;
			commandPrompt(value);
		}
		else if (dataType==4)
		{
			string value;
			commandPrompt(value);
		}
		else if (dataType==5)
		{
			bool value;
			commandPrompt(value);
		}
	
}


template <typename T>
void commandPrompt( T value)
{
	cout<<"\nNow accepting commands (quit to exit program):\n";
	PriorityQueue<T> q;
	string command;
	int priority;
	// Implement command prompt loop
	while(command.compare("quit"))
	{
		cout<<"> ";
		cin>>command;

		if (!command.compare("enqueue"))
		{
			cin>>value;
			cin>>priority;
			q.enqueue(value, priority);
		}
			
		else if (!command.compare("dequeue"))
		{
			if(!q.isEmpty())
			{
				cout<<q.dequeue()<<endl;
			}
			else cout<<"False\n";
			
		}
		else if (!command.compare("first"))
		{
			cout<<q.first()<<endl;
		}
	
		else if (!command.compare("empty"))
		{
			cout<<q.isEmpty()<<endl;
		}
		else if (!command.compare("clear"))
		{
			q.clear();
		}
	
		else if (!command.compare("quit"))
		{
			cout<<"\nExiting Program.\n";
			
		}
		else cout<<"Invalid Command\n";
	}
}
