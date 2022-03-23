#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
	private:
		int row, column;
		
	public:
		int **matrix;
		
		//Non-Default Contructure that initiate matrix's demension
		Matrix (int numRow, int numColumn)
		{
			row = numRow;
			column = numColumn;
			matrix = new int*[row];
			for(int i = 0; i < row; i++)
			{
				matrix[i] = new int[column];
    		}
    	}
		
		//Calculation functions' prototypes
		Matrix* add(Matrix&); 
		Matrix* multiply(Matrix&); 
		Matrix* subtract(Matrix&);
		Matrix* scalarMultiply(int);
		
		//Getter Funtions
		int getRow()
		{
			return row;
		};
		
		int getColumn()
		{
			return column;
		}; 
		
		//Print the result of calculation (Prototype)
		void printMatrix(Matrix *);
		
		//Destructor
		~Matrix()
		{
			delete[]matrix;
		}
};


/**************************Matrix Class's function definitions***************************/

//Matrix Addition
Matrix* Matrix::add( Matrix& m)
{
	Matrix *sum = new Matrix( getRow(),getColumn() ); 
	
	for (int i=0; i<getRow();i++)
	{
		for (int k=0; k<getColumn();k++)
		{
			//passing value from Matrix 1 to "sum"'s matrix
			sum->matrix[i][k]=matrix[i][k];
			//adding 2 matrices (Matrix 1 + Matrix 2)
			sum->matrix[i][k]+=m.matrix[i][k];
		}
	}
	return sum;
}

//Matrix Subtraction
Matrix* Matrix::subtract( Matrix& m)
{
	Matrix *difference = new Matrix(getRow(),getColumn()); 
	
	for (int i=0; i<getRow();i++)
	{
		for (int k=0; k<getColumn();k++)
		{	
			//Matrix 1 subtract Matrix 2 
			difference->matrix[i][k]=matrix[i][k] - m.matrix[i][k];
		}
	}
	return difference;
}

//Matrix Multiplication
Matrix* Matrix::multiply(Matrix& m)
{
	Matrix *product = new Matrix( getRow(),m.getColumn() ); // Row is of the first matrix and column is of the second matrix (matrix multiplication rule)
	int sum=0;
	for (int i=0; i<getRow();i++)
	{
		for (int k=0;k<m.getColumn();k++)
		{
			for (int l=0; l<m.getRow();l++)
			{
				/*Calculate the value in each element of the "product"'s matrix by summing 
				each product between Matrix 1's elements and Matrix 2's elements performed according to matrix multiplication rule*/
				sum+=matrix[i][l]*m.matrix[l][k]; 
			}
			product->matrix[i][k]=sum; //Set each element of "product"'s matrix to sum
			sum=0; //reset sum to 0 so that the previous values don't get carry to the next element
		}
	}
	return product;
}

//Matrix Scalar Multiplication
Matrix* Matrix::scalarMultiply(int scalar)
{
	Matrix *scalarProduct = new Matrix( getRow(),getColumn() );
	for (int i=0; i<getRow(); i++)
	{
		for (int k=0; k<getColumn();k++)
		{
			//Assign original matrix value for "scalarProduct"'s matrix
			scalarProduct->matrix[i][k]=matrix[i][k];
			//Multiply each element in 'scalarProduct' with scalar value 
			scalarProduct->matrix[i][k]*=scalar;
		}
	}
	return scalarProduct;
}

//Print the result of calculation
void Matrix::printMatrix(Matrix* result)
{
	for (int i=0; i<result->getRow();i++)
	{
		for (int k=0;k<result->getColumn();k++)
		{
			cout<<setw(4)<<result->matrix[i][k]<<" ";
		}
		cout<<endl;	
	}
}
