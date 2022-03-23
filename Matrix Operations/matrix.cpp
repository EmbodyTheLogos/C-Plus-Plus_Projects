// Name: Long Nguyen
// Email: lhn50323@psu.edu
// Class: CMPSC 122, Section 001
// Program: 1.1
// Due Date: February 11, 2018
//
// Description: This program collects information from the user
// to create two matrices using a Matrix class definition, and 
// performs several calculations using those matrices.
// The results of each calculation are retrieved and displayed
// to the user in a readable format.
//
// Acknowledgements: -Templates from Professor Riojas
//                   -"Matrix Multiplication in C++ By Hamas Ahmad" (https://www.youtube.com/watch?v=K92Hgo3jpwc)

#include <iostream>
#include "Matrix.h"
using namespace std;

 int main(){
	
	int scalar = 5;
	int getRow, getColumn,size, value;
	
	//Initiate matrix 1  by getting its dimension
	cout<<"Number of row in Matrix 1: ";
	cin>>getRow;
	cout<<"Number of column in Matrix 1: ";
	cin>>getColumn;
	size = getRow*getColumn;
	Matrix *m1 = new Matrix(getRow, getColumn);	
	
	//Get values for matrix 1 from user input
	cout<<"Values of Matrix 1 (expecting " <<size<<"): ";
		for (int i=0;i<getRow;i++)
			for (int k=0;k<getColumn;k++)
			{
				cin>>value;
				m1->matrix[i][k] = value;
			}
			
	//Initiate matrix 2  by getting its dimension		
	cout<<"Number of row in Matrix 2: ";
	cin>>getRow;
	cout<<"Number of column in Matrix 2: ";
	cin>>getColumn;
	size = getRow*getColumn;
	Matrix *m2 = new Matrix(getRow, getColumn);
		
		
	//Get values for matrix 2 from user input
	cout<<"Values of Matrix 2 (expecting " <<size<<"): ";
	for (int i=0;i<getRow;i++)
		for (int k=0;k<getColumn;k++)
		{
			cin>>value;
			m2->matrix[i][k] = value;
		}
		
/**************************PERFORMING CALCULATIONS****************************/			

cout<<"\n------------------------------------------------\n";

	//Check to see if the dimension of matrices are equal or not for adding and subtracting matrices
	if(m1->getRow()==m2->getRow()&&m1->getColumn()==m2->getColumn())
	{
		cout<<"Sum of 2 matrices:\n"<<endl;
		m1->printMatrix(m1->add(*m2));
		cout<<"\n------------------------------------------------\n";
		
		cout<<"Difference between 2 matrices:\n"<<endl;
		m1->printMatrix(m1->subtract(*m2));
		cout<<"\n------------------------------------------------\n";
	}
	else 
	{
		cout<<"\n***Addition and Subtraction of 2 matrices have been skipped.***\n";
		cout<<"\n------------------------------------------------\n";
	}
	
	//Check to see if the column of first matrix == the row of second matrix for multiplication
	if(m1->getColumn()==m2->getRow())
	{
		cout<<"Product of 2 matrices:\n"<<endl;
		m1->printMatrix(m1->multiply(*m2));
		cout<<"\n------------------------------------------------\n";
	}
	else
	{
		cout<<"\n***Multiplication of 2 matrices has been skipped.***\n";
		cout<<"\n------------------------------------------------\n";
	}
	
	//Scalar Multiplication of Matrix 1
	cout<<"Scalar product of Matrix 1 | Scalar = "<<scalar<<")\n"<<endl;
	m1->printMatrix(m1->scalarMultiply(scalar));
	cout<<"\n------------------------------------------------\n";
	//Scalar Multiplication of Matrix 2
	cout<<"Scalar product of Matrix 2 | Scalar = "<<scalar<<")\n"<<endl;
	m2->printMatrix(m2->scalarMultiply(scalar));
	
}
