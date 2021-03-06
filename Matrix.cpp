#include <iostream>
#include "Matrix.hpp"
#include <fstream>
#include <utility>

//copy constructor
Matrix::Matrix(const Matrix& m)
{
	mSize_r = m.mSize_r;
	mSize_c = m.mSize_c;

	mData = new double* [m.mSize_r];

	for(int i = 0; i<m.mSize_r; i++)
	{
		mData[i] = new double [mSize_c];
		for (int j = 0; j < mSize_c; ++j)
		{
			mData[i][j] = m.mData[i][j];
		}
	}
}
// copy (conversion) constructor that makes a Matrix out of a Vector
Matrix::Matrix(const Vector& v)
{	
	int m = length(v);
	mSize_r = m;
	mSize_c = 1;

	mData = new double* [m];
	for (int i = 0; i < m; ++i)
	{
		mData[i] = new double [1];
		
		mData[i][0] = v(i+1);
	}
}

// constructor that creates vector of given size with
// double precision entries all initially set to zero
Matrix::Matrix(int sizeVal_r, int sizeVal_c)
{
	mSize_r = sizeVal_r;
	mSize_c = sizeVal_c;
	// std::cout<<mSize_r;

	mData = new double* [sizeVal_r];

	for(int i = 0; i<sizeVal_r; i++)
	{
		mData[i] = new double [sizeVal_c];
		for (int j = 0; j < sizeVal_c; ++j)
		{
			mData[i][j] = 0.0;
		}
	}
}

// initialisation constructor
Matrix::Matrix(const double arr[], int sizeVal_r, int sizeVal_c)
{
	mSize_r = sizeVal_r;
	mSize_c = sizeVal_c;

	mData = new double* [sizeVal_r];

	for(int i = 0; i<sizeVal_r; i++)
	{
		mData[i] = new double [sizeVal_c];
		for (int j = 0; j < sizeVal_c; ++j)
		{
			mData[i][j] = arr[sizeVal_c*i+j];
		}
	}
}

// initialisation constructor
Matrix::Matrix(const Vector& vector, int sizeVal_r, int sizeVal_c)
{
		mSize_r = sizeVal_r;
		mSize_c = sizeVal_c;
		mData = new double* [sizeVal_r];

		for(int i = 0; i<sizeVal_r; i++)
		{
			mData[i] = new double [sizeVal_c];
			for (int j = 0; j < sizeVal_c; ++j)
			{
				mData[i][j] = vector(sizeVal_c*i+j+1);
			}
		}
}


// Matrix destructor
Matrix::~Matrix()
{
	for (int i = 0; i < mSize_r; ++i)
	{
		delete[] mData[i];
	}
	delete[] mData;
}

// Function to get number of rows of matrix
int Matrix::GetNumberofRows() const
{
	return mSize_r;
}

//Function to get number of columns of matrix
int Matrix::GetNumberofColumns() const
{
	return mSize_c;
}


// definition of + between two matrices
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	int m;
	int n;

	if (m1.mSize_r > m2.mSize_r)
	{
		m = m1.mSize_r; 
	}
	else
	{
		m = m2.mSize_r;
	}

	if (m1.mSize_c > m2.mSize_c)
	{
		n = m1.mSize_c; 
	}
	else
	{
		n = m2.mSize_c;
	}

	Matrix w(m,n);
	// add the matrices
	if (m1.mSize_r == m2.mSize_r) 
	{
		// std::cout<<m1.mSize_c<<m2.mSize_c;
		if (m1.mSize_c == m2.mSize_c)
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for(int j=0; j<m1.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
					}
			}	
	 	}
		else if(m1.mSize_c < m2.mSize_c)
		{

			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}

				for (int j=m1.mSize_c; j < m2.mSize_c; j++)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}
			std::cerr<<"matrix add - different number of colums\n";
			std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
		}
		else //m1.mSize_c > m2.mSize_c
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m2.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}	
				for (int j = m2.mSize_c; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}
				std::cerr<<"matrix add (WHY)- different number of colums\n";
				std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
		}
	}
	//different number of rows:	
	else if (m1.mSize_r < m2.mSize_r)
	{
		if (m1.mSize_c == m2.mSize_c)
		{
			for (int j = 0; j < m1.mSize_c; ++j)
			{
				for(int i=0; i<m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}
				for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}	
		}
		else if(m1.mSize_c < m2.mSize_c)
		{

			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}
			}
			for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
			{					
				for (int j = 0; j < m2.mSize_c; j++)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}

			for (int j = m1.mSize_c; j < m2.mSize_c; ++j)
			{
				for (int i = 0; i < m2.mSize_r; ++i)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}
		
			std::cerr<<"matrix add - different number of colums\n";
			std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";

		
		}
		else //m1.mSize_c > m2.mSize_c and m1.mSize_r < m2.mSize_r
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m2.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}

				for (int j = 0; j < m1.mSize_r; ++j)
				{
					w.mData[i][j] = m1.mData[i][i];
				}
			}
			for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
			{
				for (int j = 0; i < m2.mSize_c; ++j)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}
		}
		std::cerr<<"bbbmatrix add - different number of colums\n";
		std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
	}
	else // m1.mSize_r > m2.mSize_r
	{
	if (m1.mSize_c == m2.mSize_c)
		{
			for (int j = 0; j < m2.mSize_c; ++j)
			{
				for(int i=0; i<m2.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}
				for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}	
		}
		else if(m2.mSize_c < m1.mSize_c)
		{

			for (int i = 0; i < m2.mSize_r; ++i)
				{
					for (int j = 0; j < m2.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
					}
				}
			for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
			{					
				for (int j=0; j < m1.mSize_c; j++)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}

			for (int j = m2.mSize_c; j<m1.mSize_c; ++j)
			{
				for (int i = 0; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}
		
			std::cerr<< "matrix add - different number of colums\n";
			std::cerr<< "extra entries of smaller matrix assumed to be 0.0\n";
		}
		else //m1.mSize_c < m2.mSize_c and m1.mSize_r > m2.mSize_r
		{
			for (int i = 0; i < m2.mSize_r; ++i)
			{
				for (int j = 0; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
				}
			}

			for (int j = 0; j < m2.mSize_c; ++j)
			{
				for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];	
				}
				
			}
			
			for (int i = 0; i < m2.mSize_r; ++i)
			{
				for (int j = m1.mSize_c; j < m2.mSize_c; ++j)
				{
					w.mData[i][j] = m2.mData[i][j];
				}
			}
		std::cerr<< "???matrix add - different number of colums\n";
		std::cerr<< "extra entries of smaller matrix assumed to be 0.0\n";
		}

	}
	return w;
}

//definition of the - minus operator
Matrix operator-(const Matrix& m1, const Matrix& m2)
{
	int m;
	int n;
	// std::cout<< m1.mSize_r <<m1.mSize_c;
	// std::cout<< m2.mSize_r <<m2.mSize_c;
	if (m1.mSize_r > m2.mSize_r)
	{
		m = m1.mSize_r; 
	}
	else
	{
		m = m2.mSize_r;
	}

	if (m1.mSize_c > m2.mSize_c)
	{
		n = m1.mSize_c; 
	}
	else
	{
		n = m2.mSize_c;
	}

	Matrix w(m,n);
	// add the matrices
	if (m1.mSize_r == m2.mSize_r) 
	{
		// std::cout<<m1.mSize_c<<m2.mSize_c;
		if (m1.mSize_c == m2.mSize_c)
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for(int j=0; j<m1.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]+m2.mData[i][j];
					}
			}	
	 	}
		else if(m1.mSize_c < m2.mSize_c)
		{

			for (int i = 0; i < m1.mSize_r; ++i)
				{
					for (int j = 0; j < m1.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}

					for (int j=m1.mSize_c; j < m2.mSize_c; j++)
					{
						w.mData[i][j] = -m2.mData[i][j];
					}
				}
				std::cerr<<"matrix subtr - different number of colums\n";
				std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
		}
		else //m1.mSize_c > m2.mSize_c
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m2.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}	
				for (int j = m2.mSize_c; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}
				std::cerr<<"matrix subtr - different number of colums\n";
				std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
		}
	}
	//different number of rows:	
	else if (m1.mSize_r < m2.mSize_r)
	{
		if (m1.mSize_c == m2.mSize_c)
		{
			for (int j = 0; j < m1.mSize_c; ++j)
			{
				for(int i=0; i<m1.mSize_r; ++i)
					{
					w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}
				for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
				{
					w.mData[i][j] = -m2.mData[i][j];
				}
			}	
		}
		else if(m1.mSize_c < m2.mSize_c)
		{

			for (int i = 0; i < m1.mSize_r; ++i)
				{
					for (int j = 0; j < m1.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}
				}
			for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
			{					
				for (int j = 0; j < m2.mSize_c; j++)
				{
					w.mData[i][j] = -m2.mData[i][j];
				}
			}

			for (int j = m1.mSize_c; j < m2.mSize_c; ++j)
			{
				for (int i = 0; i < m2.mSize_r; ++i)
				{
					w.mData[i][j] = -m2.mData[i][j];
				}
			}
		
			std::cerr<<"matrix subtr - different number of colums\n";
			std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";		
		}
		else //m1.mSize_c > m2.mSize_c and m1.mSize_r < m2.mSize_r
		{
			for (int i = 0; i < m1.mSize_r; ++i)
			{
				for (int j = 0; j < m2.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
				}

				for (int j = 0; j < m1.mSize_r; ++j)
				{
					w.mData[i][j] = m1.mData[i][i];
				}
			}
			for (int i = m1.mSize_r; i < m2.mSize_r; ++i)
			{
				for (int j = 0; i < m2.mSize_c; ++j)
				{
					w.mData[i][j] = -m2.mData[i][j];
				}
			}
		}
		std::cerr<<"matrix subtr - different number of colums\n";
		std::cerr<<"extra entries of smaller matrix assumed to be 0.0\n";
	}
	else // m1.mSize_r > m2.mSize_r
	{
	if (m1.mSize_c == m2.mSize_c)
		{
			for (int j = 0; j < m2.mSize_c; ++j)
			{
				for(int i=0; i<m2.mSize_r; ++i)
					{
					w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}
				for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}	
		}
		else if(m2.mSize_c < m1.mSize_c)
		{

			for (int i = 0; i < m2.mSize_r; ++i)
				{
					for (int j = 0; j < m2.mSize_c; ++j)
					{
						w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
					}
				}
			for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
			{					
				for (int j=0; j < m1.mSize_c; j++)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}

			for (int j = m2.mSize_c; j<m1.mSize_c; ++j)
			{
				for (int i = 0; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];
				}
			}
		
			std::cerr<< "matrix subtr - different number of colums\n";
			std::cerr<< "extra entries of smaller matrix assumed to be 0.0\n";

		
		}
		else //m1.mSize_c < m2.mSize_c and m1.mSize_r > m2.mSize_r
		{
			for (int i = 0; i < m2.mSize_r; ++i)
			{
				for (int j = 0; j < m1.mSize_c; ++j)
				{
					w.mData[i][j] = m1.mData[i][j]-m2.mData[i][j];
				}
			}

			for (int j = 0; j < m2.mSize_c; ++j)
			{
				for (int i = m2.mSize_r; i < m1.mSize_r; ++i)
				{
					w.mData[i][j] = m1.mData[i][j];	
				}
				
			}
			
			for (int i = 0; i < m2.mSize_r; ++i)
			{
				for (int j = m1.mSize_c; j < m2.mSize_c; ++j)
				{
					w.mData[i][j] = -m2.mData[i][j];
				}
			}

		std::cerr<< "matrix subtr - different number of colums\n";
		std::cerr<< "extra entries of smaller matrix assumed to be 0.0\n";
		}

	}
	return w;
}

std::ostream& operator<<(std::ostream& output, const Matrix& m) 
{	
  for (int i=0; i< m.mSize_r; i++)
    { 
    	for (int j = 0; j < m.mSize_c; ++j)
    	{
    		output << m.mData[i][j];
    		if (j != m.mSize_c-1)
			{
				output  << "\t";
    		}
      		else
			{
				output  << std::endl;
			}
    	}
    }
  return output;  // for multiple << operators.
}

// Function to write a matrix to a CSV file
void writetoCSV(const Matrix& m)
{
	std::ofstream out("moutput.csv");
	assert(out.is_open());
	out << m;
	out.close();
	return;
}

// Function that multiplies two matrices
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	Matrix B(m1.mSize_r,m2.mSize_c);
	assert(m1.mSize_c == m2.mSize_r);

	for (int i = 0; i < m1.mSize_r; ++i)
	{
		for (int j = 0; j < m2.mSize_c; ++j)
		{
			B.mData[i][j]=0.0;
			for (int k = 0; k < m1.mSize_c; ++k)
			{
				B.mData[i][j] += B.mData[i][j] + m1.mData[i][k]*m2.mData[k][j];
			}
		}
	}
	return B;
}

// Function that multiplies matrix and scalar
Matrix operator*(const double& a, const Matrix& m2)
{
	for (int i = 0; i < m2.mSize_r; ++i)
	{
		for (int j = 0; j < m2.mSize_c; ++j)
		{
			m2.mData[i][j] = a*m2.mData[i][j];
		}
	}
	return m2;
}

// Function that multiplies scalar and matrix
Matrix operator*(const Matrix& m2, const double& a)
{
	return a*m2;
}
// Definition of division of a matrix by a scalar
Matrix operator/(const Matrix& m1, const double& a)
{
	if(a == 0.0)
	{
		throw Exception("div 0", "Attempt to divide by zero");
	}
	
	return m1*(1.0/a); 
}
// Defintion of multipl. of matrix by a vector
Vector operator*(const Matrix& m,  const Vector& v)
{
	assert(m.mSize_c == length(v));
	double array[m.mSize_r];

	for (int i = 0; i < m.mSize_r; ++i)
	{	
		array[i] = 0;
		for (int j = 0; j < m.mSize_c; ++j)
		{
			array[i] += m.mData[i][j]*v(j+1);	
		}
	}
	Vector ans(array, m.mSize_r);
	return ans;
}

// Definition of multipl. of vector b a matrix
Vector operator*(const Vector &v, const Matrix& m)
{
	assert(m.mSize_r == length(v));
	double array[m.mSize_c];
	for (int j = 0; j < m.mSize_c; ++j)
	{
		array[j]=0;

		for (int i = 0; i < m.mSize_r; ++i)
		{
			array[j] += m.mData[i][j]*v(i+1);
		}
	}
	Vector ans(array, m.mSize_c);
	return ans;
}

// Function that creates the augmented matrix from a vector and a matrix
Matrix create_aug(const Vector& v, const Matrix& m)
{
	assert(m.mSize_r == length(v));
	Matrix aug(m.mSize_r, m.mSize_c+1);

	for(int i = 1; i<m.mSize_r+1; i++)
	{
		for(int j = 1; j<m.mSize_c+2; j++)
		{
			if(j<m.mSize_c+1){
					aug(i,j) = m.mData[i-1][j-1];
					}
			else if(j == m.mSize_c+1)
				{
				aug(i,j) = v(i);
				}
		}
	}
	return aug;
}

//definition of the unary operator - 
Matrix operator-(const Matrix& m)
{
	Matrix w(m.mSize_r, m.mSize_c);

	for (int i = 0; i < m.mSize_r; ++i)
	{
		for (int j = 0; j < m.mSize_c; ++j)
		{
			w.mData[i][j] = -m.mData[i][j];
		}
	}
	return w;
}

// return the size of a matrix
std::pair<int,int> size(const Matrix& m)
{
	return {m.mSize_r,m.mSize_c};
}


// print matrix
void print(const Matrix& m1)
{
	for (int i = 0; i < m1.mSize_r; ++i)
	{

		for (int j = 0; j < m1.mSize_c; ++j)
		{
			std::cout<< m1.mData[i][j] << "\t";
		}
	std::cout<<"\n";
	}
}

// Recursive function to calculate determinant
double det(const Matrix& m)
{
	assert(m.mSize_r == m.mSize_c);
	double determinant = 0.0;
	
	if (m.mSize_r == 1)
	{
		determinant = m.mData[0][0];
	}
	else
	{
		// More than one entry of matrix
		for (int i_outer = 0; i_outer < m.mSize_r; ++i_outer)
			{
				Matrix sub_matrix(m.mSize_r-1, m.mSize_c-1);
				for (int i = 0; i < m.mSize_r-1; ++i)
				{
					for (int j = 0; j < i_outer; ++j)
					{
							sub_matrix(i+1,j+1) = m.mData[i+1][j];
					}
					for (int j = i_outer; j < m.mSize_c-1; ++j)
					{
						sub_matrix(i+1,j+1) = m.mData[i+1][j+1];
					}
				}
			double sub_matrix_determinant = det(sub_matrix);

			determinant += pow(-1.0,i_outer) * m.mData[0][i_outer]*sub_matrix_determinant;
			}	
	}
	return determinant;
}

// Function that cuts matrix
Matrix cut(const Matrix& m, int new_m, int new_n)
{
	int min_rows;
	int min_columns;

	// Find the minimum of the new_m and new_m and row/column size of the matrix
	if (m.mSize_r < new_m)
	{
		min_rows = m.mSize_r;
	}
	else
	{
		min_rows = new_m;
	}

	if(m.mSize_c < new_n)
	{
		min_columns = m.mSize_c;
	}
	else
	{
		min_columns = new_n;
	}
	// Create new matrix and fill
	Matrix new_matrix(new_m,new_n);
	for (int i = 0; i < min_rows; ++i)
	{
		for (int j = 0; j < min_columns; ++j)
		{
			new_matrix.mData[i][j] = m.mData[i][j];
		}
	}

	return new_matrix;
}

//definition of the matrix operation =
Matrix& Matrix::operator=(const Matrix& m)
{
// Check if matrices have the same dimensions,
// if rhs has smaller dimensions than lhs, assume missing entries are 0
// if rhs has larger dimensions than lhs, then throw
	if ((m.mSize_c > mSize_c)||(m.mSize_r> mSize_r))
	{
		throw Exception("dimensions mismatch", "matrix assignment operator - matrices have different dimensions");
	}
	else if ((m.mSize_r < mSize_r) && (m.mSize_c < mSize_c))
	{

		// Copy the rhs values in the lhs matrix
		for (int i = 0; i < m.mSize_r; ++i)
		{
			for (int j = 0; j < m.mSize_c; ++j)
			{
				mData[i][j] = m.mData[i][j];
			}
		}
		// Fill the remainder of the lhs matrix with zeroes
		for (int i = m.mSize_r; i < mSize_r; ++i)
		{
			for (int j = 0; j < mSize_c; ++j)
			{
				mData[i][j] = 0.0;	
			}
		}

		for (int j = m.mSize_c; j < mSize_c; ++j)
		{
			for (int i = 0; i < m.mSize_r; ++i)
			{
				mData[i][j] = 0.0;
			}
		}

	}
	return *this;
}

double& Matrix::operator()(int i, int j)
{
	if ((i < 1)||(j<1))
	{
		throw Exception("out of range", "accessing matrix through () - index too Small");
	}
	else if ((i>mSize_r)||(j>mSize_c))
	{
		throw Exception("out of range","accessing vector through () - index too high");
	}
	return mData[i-1][j-1];
}

// Definition of backslash operator
Vector operator/(const Matrix& m, const Vector& v)
{
	//assert that the matrix is square	
	assert(m.mSize_c == m.mSize_r);
	// make sure that the matrix is non-singular
	try
	{
		if (det(m) == 0)
		{
			throw Exception("inverse non-existent", "Matrix is singular");	
		}
	}
	catch (Exception& err)
	{
    	err.DebugPrint();
	}
	// Create the augmented matrix of the system
	Matrix augmented = create_aug(v, m);
	//Bring the system to triangular form by GE
	augmented.Gaussian_elimination();
	//return the solution (vector) of the triangular system
	return augmented.solve_triangular();	
}

// Helper function for the backslash, that performs GE on a matrix
void Matrix::Gaussian_elimination()
{	
	int m = mSize_r;
	int n = mSize_c;
	int h = 0;
	int k = 0;
	while( h<m and k<m)
	{
		// find pivot
		int max_p=h;
		for(int l = h; l<m; l++)
		{
			if(std::fabs(mData[l][k])>std::fabs(mData[max_p][k]))
			{
				max_p = l;
			}
		}
		// Now we know what the max pivot is.
		// swap rows
		if(max_p != h)
		{
			double ph[m+1];
			for(int kk = 0; kk<m+1; kk++)
				{
					ph[kk] =mData[h][kk];
				}

			for(int jj = 0; jj<m+1; jj++)
			{
				mData[h][jj] = mData[max_p][jj];
			}

			for(int ll = 0; ll<m+1; ll++)
			{
				mData[max_p][ll] = ph[ll];
			}
		}

		if(mData[h][k]!=0)
		{
			for(int mm = (h+1); mm <m; mm++)
			{
				double AA = (mData[mm][k]/mData[h][k]);
				for(int oo = k; oo<m+1; oo++)
				{
					mData[mm][oo] = mData[mm][oo] - AA*mData[h][oo];
				}
			}
		}
		k+=1;
		h+=1;
	}
}

// Helper function for backslash, solve triangular system
Vector Matrix::solve_triangular()
{
	int n = mSize_c;
	int m = mSize_r;

	double x[m];
	for (int i=m-1; i>=0; i--)
	{
		x[i] = mData[i][n-1]/mData[i][i];


		for (int k=i-1;k>=0; k--)
		{
			mData[k][n-1] -= mData[k][i] * x[i];
		}
	}
	return Vector(x,m);
}

// Function that generates n-dimensional identity
Matrix eye(int n)
{
	double data[n*n];
	for (int i = 0; i < n*n; ++i)
	{
		if (i%(n+1) == 0)
		{
			data[i] = 1;
		}
		else
		{
			data[i]=0;
		}
	}
	Matrix I(data,n,n);
	return I;
}
// Function that generates m by n zero matrix
Matrix zeros(int m, int n)
{
	Matrix M(m,n);
	return M;
}

// Funciton that creates diagonal matrix with v on diagonal.
Matrix diag(const Vector& v, int k)
{	int n = length(v)+std::abs(k);
	double data[n*n];
	int l = 0;
	for (int i = 0; i < n*n; ++i)
	{
		if ((i-k)%(n+1) == 0 && l < length(v))
		{	
			data[i] = v(l+1);
			l+=1;
		}
		else
		{
			data[i]=0;
		}
	}
	Matrix D(data,n,n);
	return D;
}

//construct sparse trid matrix of given size
// the first element of the superdiagonal is set to zero but is not part of the matrix,
// the last element of the subdiagonal is set to zero but is not part of the matrix.
sparse_trid::sparse_trid(int sizeVal)
{
	mSize = sizeVal;

	superdiagonal = new double [sizeVal];
	diagonal = new double [sizeVal];
	subdiagonal = new double [sizeVal];

	for (int i = 0; i < sizeVal; ++i)
	{
		superdiagonal[i] = 0.0;
		diagonal[i] = 0.0;
		subdiagonal[i] = 0.0;
	}
}

// Constructor of sparse trid matrix with 3 arrays
sparse_trid::sparse_trid(int sizeVal, double superd[], double d[], double subd[])
{
	mSize = sizeVal;

	superdiagonal = new double [sizeVal];
	diagonal = new double [sizeVal];
	subdiagonal = new double [sizeVal];

	superdiagonal[0] = 0.0;
	diagonal[0] = d[0];
	subdiagonal[0] = subd[0];

	for (int i = 1; i < sizeVal-1; ++i)
	{
		superdiagonal[i] = superd[i-1];
		diagonal[i]=d[i];
		subdiagonal[i] = subd[i];
	}
	superdiagonal[sizeVal-1] = superd[sizeVal-2];
	diagonal[sizeVal-1] = d[sizeVal-1];
	subdiagonal[sizeVal-1] = 0.0;
}
// Sparse trid destructor
sparse_trid::~sparse_trid()
{
	delete[] superdiagonal;
	delete[] diagonal;
	delete[] subdiagonal;
}

// Function to get number of rows of matrix
int sparse_trid::GetNumberofRows() const
{
	return mSize;
}

// Function to get number of rows of matrix
int sparse_trid::GetNumberofColumns() const
{
	return mSize;
}

// Print function for the sparse_trid matrix
void print(const sparse_trid& S)
{
	std::cout<<"superdiagonal: \n";
	std::cout<<"[";
	for (int i = 0; i < S.mSize; ++i)
	{
		std::cout<<S.superdiagonal[i];
		if (i<S.mSize-1)
		{
			std::cout<< ", ";
		}
	}
	std::cout<<"]\n";

	std::cout<<"diagonal: \n";
	std::cout<<"[";
	for (int i = 0; i < S.mSize; ++i)
	{
		std::cout<<S.diagonal[i];
		if (i<S.mSize-1)
		{
			std::cout<< ", ";
		}
	}
	std::cout<<"]\n";

	std::cout<<"subdiagonal: \n";
	std::cout<<"[";
	for (int i = 0; i < S.mSize; ++i)
	{
		std::cout<<S.subdiagonal[i];
		if (i<S.mSize-1)
		{
			std::cout<< ", ";
		}
	}
	std::cout<<"]\n";
}

// Multiplication operator for the sparse_trid matrix
Vector operator*(const sparse_trid& S, Vector& v)
{
	// make sure the dimensions agree
	assert(S.mSize == length(v));
	// create a vector
	Vector product(S.mSize);
	// fill in its first value
	product(1) = S.diagonal[0]*v(1)+S.superdiagonal[1]*v(2);
	// calculate the non-boundary entries of the vector
	for (int i = 2; i < S.mSize; ++i)
	{	
		product(i)=v(i-1)*S.subdiagonal[i-2]+v(i)*S.diagonal[i-1]+v(i+1)*S.superdiagonal[i];
	}
	//calculate last vector entrie
	product(S.mSize) = S.diagonal[S.mSize-1]*v(S.mSize)+S.subdiagonal[S.mSize-2]*v(S.mSize-1);
	return product;
}

// Conversion function from sp to dense matrix
Matrix sparse_trid2dense(const sparse_trid& S)
{
	int n = S.mSize;
	Matrix D(n,n);
	D(1,1) = S.diagonal[0];
	D(1,2) = S.superdiagonal[1];

	for (int i = 2; i <= n-1; ++i)
	{	
		for (int j = i-1; j <= i+1; ++j)
			{
				if (i-j == 0)
				{
					D(i,j) = S.diagonal[i-1];
				}

				else if (i-j == -1)
				{
					D(i,j) = S.superdiagonal[i];
				}

				else if (i-j == 1)
				{
					D(i,j) = S.subdiagonal[i-2];
				}
			}	
	}
	D(n,n) = S.diagonal[n-1];
	D(n,n-1) = S.subdiagonal[n-2];
	return D;
}