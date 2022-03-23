#include <iostream>
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
		
		//Getter Funtions
		int getRow()
		{
			return row;
		};
		
		int getColumn()
		{
			return column;
		}; 
		
		//Destructor
		~Matrix()
		{
			delete[]matrix;
		}
		
		//Overload operators to replicate Matrix Class public functions
		friend Matrix* operator+( Matrix&, Matrix&);
		friend Matrix* operator-( Matrix&,  Matrix&);
		friend Matrix* operator*( Matrix&,  Matrix&);
		friend Matrix* operator*( int, Matrix&);
		friend ostream& operator<<(ostream&,  Matrix&);
		friend istream& operator>>(istream&, Matrix&);

};
