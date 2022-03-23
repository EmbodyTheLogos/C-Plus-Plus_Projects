//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn50327@psu.edu
// Class: CMPSC 122, Section 001
// Program 1.2
// Due Date: February 11, 2018, 11:59 PM
//
// Description: This program collects information from the user
// to create two matrices using a Matrix class definition, and 
// performs several calculations using those matrices.
// The results of each calculation are retrieved and displayed
// to the user in a readable format.
//
// Acknowledgements: Templates from Professor Riojas 
//					"Overloading the << Operator for Your Own Classes" (https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx)
//					"Overloading the >> Operator for Your Own Classes" (https://msdn.microsoft.com/en-us/library/x6aebccc.aspx)
//---------------------------------------------------------------------


#include "Matrix_OPS.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Overload '+' operator to replicate the add function in Matrix class
Matrix* operator+(Matrix&m1, Matrix&m2)
{
	Matrix *sum = new Matrix( m1.getRow(),m1.getColumn() ); 
	
	for (int i=0; i<m1.getRow();i++)
	{
		for (int k=0; k<m1.getColumn();k++)
		{
			//Adding to matrices
			sum->matrix[i][k] = (m1.matrix[i][k]) + (m2.matrix[i][k]);
		}
	}
	return sum;
}

//Overload '-' operator to replicate the subtract function in Matrix class
Matrix* operator-(Matrix&m1, Matrix&m2)
{
	Matrix *difference = new Matrix( m1.getRow(),m1.getColumn() ); 
		
	for (int i=0; i<m1.getRow();i++)
	{
		for (int k=0; k<m1.getColumn();k++)
		{
			//passing value to matrix 1 and matrix 2 from m1 and m2, respectively
			difference->matrix[i][k]=m1.matrix[i][k]-m2.matrix[i][k];
		}
	}
	return difference;
}

//Overload '*' operator to replicate the multiply function in Matrix class
Matrix* operator*(Matrix&m1, Matrix&m2)
{
	Matrix *product = new Matrix( m1.getRow(),m2.getColumn() ); // Row is of the first matrix and column is of the second matrix (matrix multiplication rule)
	int sum=0;
	for (int i=0; i<m1.getRow();i++)
	{
		for (int k=0;k<m2.getColumn();k++)
		{
			for (int l=0; l<m2.getRow();l++)
			{
				/*Calculate the value in each element of the "product"'s matrix by summing 
				each product between Matrix 1's elements and Matrix 2's elements performed according to matrix multiplication rule*/
				sum+=m1.matrix[i][l]*m2.matrix[l][k]; 
			}
			product->matrix[i][k]=sum; //Set each element of "product"'s matrix to sum
			sum=0; //reset sum to 0 so that the previous values don't get carry to the next element
		}
	}
	return product;
}

//Overload '*' operator to replicate the scalar multiply function in Matrix class
Matrix* operator*(Matrix&m, int scalar)
{
	Matrix *scalarProduct = new Matrix( m.getRow(),m.getColumn() );
	for (int i=0; i<m.getRow(); i++)
	{
		for (int k=0; k<m.getColumn();k++)
		{
			//Multiply each element in 'scalarProduct' with scalar value 
			scalarProduct->matrix[i][k]= (m.matrix[i][k] * scalar);
		}
	}
	return scalarProduct;
}

//Overload operator '<<' to replicate printMatrix function in Matrix Class
ostream& operator<<(ostream& os,  Matrix&result)
{
	for (int i=0; i<result.getRow();i++)
	{
		for (int k=0;k<result.getColumn();k++)
		{
			os<<setw(4)<<result.matrix[i][k]<<" ";
		}
		os<<endl;	
	}
	return os;
}

//Overload operator '>>' to get input for matrix's elements
istream& operator>>(istream& is, Matrix&m)
{
	int value;
	for (int i=0;i<m.getRow();i++)
		for (int k=0;k<m.getColumn();k++)
		{
			is>>value;
			m.matrix[i][k] = value;
		}
	return is;
}

int main()
{
	int scalar = 5;
	int getRow, getColumn,size;
	
	//Initiate matrix 1  by getting its dimension
	cout<<"Number of row in Matrix 1: ";
	cin>>getRow;
	cout<<"Number of column in Matrix 1: ";
	cin>>getColumn;
	size = getRow*getColumn;
	Matrix *matrix1 = new Matrix(getRow, getColumn);	
	
	//Get values for matrix 1 from user input
	cout<<"Values of Matrix 1 (expecting " <<size<<"): ";
		cin>>*matrix1;
		
	
	//Initiate matrix 2  by getting its dimension
	cout<<"Number of row in Matrix 2: ";
	cin>>getRow;
	cout<<"Number of column in Matrix 2: ";
	cin>>getColumn;
	size = getRow*getColumn;
	Matrix *matrix2 = new Matrix(getRow, getColumn);	
	
	//Get values for matrix 2 from user input
	cout<<"Values of Matrix 2 (expecting " <<size<<"): ";
		cin>>*matrix2;
	

/**************************PERFORMING CALCULATIONS****************************/			
cout<<"\n------------------------------------------------\n";

	//Check to see if the dimension of matrices are equal or not for adding and subtracting matrices
	if(matrix1->getRow()==matrix2->getRow() && matrix1->getColumn()==matrix2->getColumn())
	{
		cout<<"Sum of 2 matrices:\n"<<endl;
		cout<< *(*matrix1+*matrix2); // Calling '+' function
		cout<<"\n------------------------------------------------\n";
		
		cout<<"Difference between 2 matrices:\n"<<endl;
		cout<<*(*matrix1-*matrix2); //Calling '-' function
		cout<<"\n------------------------------------------------\n";
	}
	else 
	{
		cout<<"\n***Addition and Subtraction of 2 matrices have been skipped.***\n";
		cout<<"\n------------------------------------------------\n";
	}
	
	//Check to see if the column of first matrix == the row of second matrix for multiplication
	if(matrix1->getColumn()==matrix2->getRow())
	{
		cout<<"Product of 2 matrices:\n"<<endl;
		cout<<*(*matrix1 * *matrix2); //Calling '*' (multiply) function
		cout<<"\n------------------------------------------------\n";
	}
	else
	{
		cout<<"\n***Multiplication of 2 matrices has been skipped.***\n";
		cout<<"\n------------------------------------------------\n";
	}
	
	//Scalar Multiplication of Matrix 1
	cout<<"Scalar product of Matrix 1 | Scalar = "<<scalar<<")\n"<<endl;
	cout<<*(*matrix1* scalar); //Calling '*' (scalar multiply) function
	cout<<"\n------------------------------------------------\n";
	//Scalar Multiplication of Matrix 2
	cout<<"Scalar product of Matrix 2 | Scalar = "<<scalar<<")\n"<<endl;
	cout<<*(*matrix2* scalar); //Calling '*' (scalar multiply) function
}
