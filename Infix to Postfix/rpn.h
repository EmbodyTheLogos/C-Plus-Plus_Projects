//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: rpn.h
//
// Description: Contains functions for rpn.cpp
//
//---------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>	//used for exit(1)
#include <string>
#include "stack_int.h"
#include <sstream>	//Used for convert a string to int
using namespace std;



void validate(string);
int operatorPriority(char);
bool isOperator(char);
int operation(char, int, int);
int evaluationRPN(string);

//check to see if the character is an operator
bool isOperator(char o)
{
	if ( o== '+' || o== '-' || o== '*'|| o== '/')
	{
		return true;
	}
	else return false;
}

//initiate priority for operators
int operatorPriority(char o)
{
	int priority;
	
	switch (o)
	{
		case '+': priority=1; break;
		case '-': priority=1; break;
		case '*': priority=2; break;
		case '/': priority=2; break;
		default: priority = -1;
	}

	return priority;
}


//Check for expression validity (infix)
void validate(string value)
{
	for(int i = 0; i<value.size();i++)
	{
		//If operators or closed parenthesis is at the beginning of expression
		if(i==0)
		{
			if(value[i]=='+' || value[i]=='-'|| value[i] == '*' || value[i] == '/'|| value[i]==')')
			{
				cout<<"Invalid Expression!\n";
				exit(1);
			}
		}		
		
		//If a character in string is not an operator, operand, space, and parentheses
		if(!isOperator(value[i]) && !isdigit(value[i]) && value[i] != ' '&& value[i] != '(' && value[i] != ')')
		{
			cout<<"Invalid Expression!\n";
			exit(1);
		}
		
		//If two operator is next to each other
		if(isOperator(value[i]) && isOperator(value[i-1]))
		{
			cout<<"Invalid Expression!\n";
			exit(1);
		}
		//if the operator is at the end of expression
		if(i==value.size()-1)
		{
			if(isOperator(value[i]))
			{
				cout<<"Invalid Expression!\n";
				exit(1);
			}
		}
	}
}

//Perform calculation based on different entered operators
int operation(char o, int operand1, int operand2)
{
	int result=0;
	if (o=='+')
	{
		result = operand1+operand2;
	}
	else if (o=='-')
	{
		result = operand1-operand2;
	}
	else if (o=='*')
	{
		result = operand1*operand2;
	}
	else if (o=='/')
	{
		result = operand1/operand2;
	}
	return result;
}

//Evaluate the RPN expression
int evaluationRPN(string rpn)
{
	string num="";
	int temp; //used to stored data to be push into stack
	int temp1;	//operand 1 to calculate
	int temp2;	//operand 2 to calculate
	int result;

	
	IntStack b;
	for(int i=0; i<rpn.size();i++)
	{
		if(isdigit(rpn[i]))
		{
			num+=rpn[i];
		}
		else if(rpn[i] == ' ')
		{
			//Convert string num to int,
			//and push the int value to b
			stringstream toInt(num);
			toInt >>temp;
			
			if(isdigit(rpn[i-1]))
			{
				b.push(temp);
			}
			
			//reset num
			num="";
		}
		else if(isOperator(rpn[i]))
		{
			temp2=b.pop();
			temp1=b.pop();		
			temp = operation(rpn[i],temp1,temp2);	
			b.push(temp);			
		}
	}
	result=b.pop();
	return result;
}

