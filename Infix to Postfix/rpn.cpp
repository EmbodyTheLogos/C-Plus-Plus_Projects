//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: rpn.cpp
//
// Description: Convert infix notation to postfix notation
//				and evaluated the postfix notation
//
// Acknowledgement: (2) Doctor Chang's Notes
//					(1) https://www.geeksforgeeks.org/converting-strings-numbers-cc					
//					(3) https://www.youtube.com/watch?v=vq-nUF0G4fI
//
//---------------------------------------------------------------------

#include "rpn.h"
#include "stack.h"
#include <iostream>
#include <string>
using namespace std;


int main()
{
string input;
	string RPN =""; //store postfix notation
	string num;		//handle multi digit number
	
	cout<<"Please enter an infix expression: ";
	getline(cin,input);
	
	validate(input);
	
	Stack a;
	
	//go through each character from string "input"
	for(int i =0; i<input.size();i++)
	{
		if(isdigit(input[i]))
		{
			RPN+=input[i]; 
		}
		else if(isOperator(input[i]))
		{
			
			if(a.isEmpty())
			{
				a.push(input[i]);
				RPN+=" "; 
			}
			else if(operatorPriority(input[i]) > operatorPriority(a.top()))
			{
				a.push(input[i]);
				RPN+=" "; 
			}
			else if(operatorPriority(input[i]) <= operatorPriority(a.top()) && operatorPriority(input[i]) != -1)
			{
				RPN+=" "; 
				RPN+=a.pop(); 
				a.push(input[i]);
				RPN+=" ";
			}			
		}		
		else if (input[i]=='(')
		{
			a.push('(');
		}
		else if(input[i] == ')')
		{
			//Pop elements from a.top() to '(', inclusively
			if (!a.isEmpty())
			{
				while(!a.isEmpty() && a.top() != '(' )
				{	
					RPN+=" "; 
					RPN+=a.pop(); 
				}
				if(a.top() == '(')
				{
					a.pop(); //Only pop '(', not outputing it
				}
			}	
		}		
		if (i==input.size()-1)
		{
			//Pop everything in the stack and check for validity
			while(!a.isEmpty())
			{
				RPN+=" "; 				
				//This check if ')' entered more times than '(',
				//leaving the stack not empty.
				if(a.top()== '(') break;
				
				RPN+=a.pop(); 		
			}
			
		}
	}
	
	//Check for expression validity (using stack)
	if(!a.isEmpty())
	{
		cout<<"Invalid Expression!\n";
	}
	else {
		cout<<"\nThe equivalent postfix expression of "<<input<<" is: \n"<<RPN<<endl;
		cout<<"\nThe result of "<<RPN<< " is: "<<evaluationRPN(RPN)<<endl;
	}
		
}


	


