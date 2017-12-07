/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 2:
	Strassen`s Matrix Multiplication
	10.19.17	
*/

#include <iostream>		/* cout, cin */
#include <math.h> 		/* log2, floor, sqrt */
#include <climits>		/* INT_MAX */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <vector>		/* vector */

using namespace std;

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indocate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs strassen matrix multiplication
void strassenMatrixMul(vector <vector <int> > &input, 
					   vector <vector <int> > &input2, 
					   vector <vector <int> > &output, int &size);

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indocate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs normal matrix multiplication
void regularMatrixMul(vector <vector <int> > &input, 
					  vector <vector <int> > &input2, 
					  vector <vector <int> > &output, int size);

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indicate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs matrix addition
void matrixAdd(vector <vector <int> > &input, 
			      vector <vector <int> > &input2, 
			      vector <vector <int> > &output, 
			      int &size);

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indicate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs matrix subtraction
void matrixSub(vector <vector <int> > &input, 
			      vector <vector <int> > &input2, 
			      vector <vector <int> > &output, 
			      int &size);

// Return: void
// Param 1: input vector to be filled ramdonly
// Param 2: size of the matrix, height and width
// Fills matrix with random integers
void fillMatrix(vector <vector <int> > &input, int n);

// Return: number of inputs
// Parameters: none
// Prompts user and validate the input
int takeUserInput();

// Return: void
// Param 1: input vector to be printed on the screen
// Param 2: size of the matrix, height and width
// Prints the values of the matrix given
void printMatrix(vector <vector <int> > input, int size);

// Return: void
// Param 1: input vector to be created
// Param 2: size of the matrix, height and width
// Creates a empty matrix with given dimension
void generateMatrix(vector <vector <int> > &input, int n);

// Main function: starting point of the program
int main ()
{
	srand(time(NULL));
	int n = takeUserInput();

	vector <vector <int> > A;
	vector <vector <int> > B;
	vector <vector <int> > result1;
	vector <vector <int> > result2;

	generateMatrix(result1, n);
	generateMatrix(result2, n);
	generateMatrix(A, n);
	generateMatrix(B, n);

	fillMatrix(A, n);
	fillMatrix(B, n);

	cout << "\nRegular Matrix Multiplication:\n\n";

	regularMatrixMul(A, B, result1, n);
	printMatrix(result1, n);

	cout << "\nStrassen Matrix Multiplication:\n\n";

	strassenMatrixMul(A, B, result2, n);
	printMatrix(result2, n);

	cout << "\n";
}

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indocate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs strassen matrix multiplication
void strassenMatrixMul(vector <vector <int> > &input, 
					   vector <vector <int> > &input2, 
					   vector <vector <int> > &output, int &size)
{
	// If the matrix size is 2 multiply them with normal method
	if (size == 2) regularMatrixMul(input, input2, output, 2);
	else
	{
		int newSize = size / 2;
		vector <int> inner(newSize);
        
        // These are empty matrises
        vector< vector<int> >  A11(newSize, inner), A12(newSize, inner), 
        					   A21(newSize, inner), A22(newSize, inner),
            				   B11(newSize, inner), B12(newSize, inner), 
            				   B21(newSize, inner), B22(newSize, inner),
            				   res1(newSize, inner), res2(newSize, inner);

        // Devide the input matrixes into 4 sub parts
		for(int i = 0; i < newSize; i++) 
		{
        	for(int j = 0; j < newSize; j++) 
            {
				A11.at(i).at(j) = input.at(i).at(j);
				A12.at(i).at(j) = input.at(i).at(j + newSize);
				A21.at(i).at(j) = input.at(i + newSize).at(j);
				A22.at(i).at(j) = input.at(i + newSize).at(j + newSize);

				B11.at(i).at(j) = input2.at(i).at(j);
				B12.at(i).at(j) = input2.at(i).at(j + newSize);
				B21.at(i).at(j) = input2.at(i + newSize).at(j);
				B22.at(i).at(j) = input2.at(i + newSize).at(j + newSize);
			}
		}

		vector< vector<int> > m1(newSize, inner);
		// M1 = (A11 + A22) * (B11 + B22)
		

		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res1.at(i).at(j) = 
        							A11.at(i).at(j) + 
           							A22.at(i).at(j);      
    	} 


    	for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res2.at(i).at(j) = 
        							B11.at(i).at(j) + 
           							B22.at(i).at(j);      
    	} 

        strassenMatrixMul(res1, res2, m1, newSize);

        vector< vector<int> > m2(newSize, inner);
 		// M2 = (A21 + A22) * B11

 		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res1.at(i).at(j) = 
        							A21.at(i).at(j) + 
           							A22.at(i).at(j);      
    	} 
 
        strassenMatrixMul(res1, B11, m2, newSize); 
 
 		vector< vector<int> > m3(newSize, inner);
 		// M3 = A11 * (B12 - B22)

 		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res2.at(i).at(j) = 
        							B12.at(i).at(j) -
           							B22.at(i).at(j);      
    	} 

        strassenMatrixMul(A11, res2, m3, newSize); 
 
 		vector< vector<int> > m4(newSize, inner);
 		// M4 = A22 * (B21 - B11)

 		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res2.at(i).at(j) = 
        							B22.at(i).at(j) -
           							B11.at(i).at(j);      
    	}

        strassenMatrixMul(A22, res2, m4, newSize); 

 		vector< vector<int> > m5(newSize, inner);
 		// M5 = (A11 + A12) * B22   

 		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res1.at(i).at(j) = 
        							A11.at(i).at(j) +
           							A12.at(i).at(j);      
    	}

        strassenMatrixMul(res1, B22, m5, newSize); 
 
        vector< vector<int> > m6(newSize, inner);
 		// M6 = (A21 - A11) * (B11 + B12)

        for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res1.at(i).at(j) = 
        							A21.at(i).at(j) -
           							A11.at(i).at(j);      
    	}


    	for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res2.at(i).at(j) = 
        							B11.at(i).at(j) +
           							B12.at(i).at(j);      
    	}

        strassenMatrixMul(res1, res2, m6, newSize); 
 
 		vector< vector<int> > m7(newSize, inner);
 		// M7 = (A12 - A22) * (B21 + B22)

 		for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res1.at(i).at(j) = 
        							A12.at(i).at(j) -
           							A22.at(i).at(j);      
    	}


    	for(int i = 0; i < size; i++) 
		{
        for(int j = 0; j < size; j++) res2.at(i).at(j) = 
        							B21.at(i).at(j) +
           							B22.at(i).at(j);      
    	}

        strassenMatrixMul(res1, res2, m7, newSize); 
 
 		vector< vector<int> > C11(newSize, inner), 
 							  C12(newSize, inner), 
 							  C21(newSize, inner), 
 							  C22(newSize, inner);
 		// C12 = M3 + M5
        matrixAdd(m3, m5, C12, newSize); 
        
        // C21 = M2 + M4
        matrixAdd(m2, m4, C21, newSize); 
 
 		// C11 = M1 + M4 + M7 - M5
        matrixAdd(m1, m4, res1, newSize); 
        matrixAdd(res1, m7, res2, newSize); 
        matrixSub(res2, m5, C11, newSize); 
 
 		// C22 = M1 + M3 - M2 + M6
        matrixAdd(m1, m3, res1, newSize); 
        matrixAdd(res1, m6, res2, newSize); 
        matrixSub(res2, m2, C22, newSize); 

        // Update the result
		for(int i = 0; i < newSize; i++) 
		{
        	for(int j = 0; j < newSize; j++) 
            {
            	output.at(i).at(j) = C11.at(i).at(j);
            	output.at(i).at(j + newSize) = C12.at(i).at(j);
            	output.at(i + newSize).at(j) = C21.at(i).at(j);
            	output.at(i + newSize).at(j + newSize) = C22.at(i).at(j);
            }
        }
	}
}

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indocate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs normal matrix multiplication
void regularMatrixMul(vector <vector <int> > &input, 
					  vector <vector <int> > &input2, 
					  vector <vector <int> > &output, int size)
{
	// Normal matrix multiplication with O(N^3)
	for(int i = 0; i < size; i++) 
	{
        for(int j = 0; j < size; j++) 
        {
           	for(int k = 0; k < size; k++)
           	{
           		output[i][k] += input[i][j] * input2[j][k];
           	}            
     	}
    }
}

// Return: void
// Param 1: input vector to be printed on the screen
// Param 2: size of the matrix, height and width
// Prints the values of the matrix given
void printMatrix(vector <vector <int> > input, int size)
{
	for(int i = 0; i < size; i++) 
	{
        for(int j = 0; j < size; j++) cout << input.at(i).at(j) << "    ";
        cout << "\n";
    }
}

// Return: void
// Param 1: input vector to be created
// Param 2: size of the matrix, height and width
// Creates a empty matrix with given dimension
void generateMatrix(vector <vector <int> > &input, int n)
{
	for (int i = 0; i < n; i++)
	{
		vector <int> row;
		for (int j = 0; j < n; j++) row.push_back(0);
		input.push_back(row);
	}
}

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indicate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs matrix addition
void matrixAdd(vector <vector <int> > &input, 
			      vector <vector <int> > &input2, 
			      vector <vector <int> > &output, 
			      int &size)
{
	for(int i = 0; i < size; i++) 
	{
        for(int j = 0; j < size; j++) output.at(i).at(j) = 
        							input.at(i).at(j) + 
           							input2.at(i).at(j);      
    } 
}

// Return: void
// Param 1: input vector to indicate a matrix
// Param 2: input vector 2 to indicate second matrix
// Param 3: matrix to hold the result
// Param 4: size of the matrixes, height and width
// Performs matrix subtraction
void matrixSub(vector <vector <int> > &input, 
			      vector <vector <int> > &input2, 
			      vector <vector <int> > &output, 
			      int &size)
{
	for(int i = 0; i < size; i++) 
	{
        for(int j = 0; j < size; j++) output.at(i).at(j) = 
        							input.at(i).at(j) - 
           							input2.at(i).at(j);      
    } 
}

// Return: number of inputs
// Parameters: none
// Prompts user and validate the input
int takeUserInput()
{
	cout << "\nEnter n = 2^k where k is a positive integer and 1 <= n <= 1024.\n";

	bool flag = true;
	int n;
	float k;

	while (flag)
	{
		flag = false;
		cin >> n;

		// Checks if input is valid
		if (n < 1 || n > 1024 || cin.fail())
		{
			cout << "Invalid input !!! 1 <= n <= 1024 !!!\nEnter again: ";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}

		k = log2(n);

		if (flag == false && (k < 1 || (k - floor(k)) > 0))
		{
			cout << "Invalid input !!! n = 2^k where k is a positive integer !!!\nEnter again: ";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}
	}

	return n;
}

// Return: void
// Param 1: input vector to be filled ramdonly
// Param 2: size of the matrix, height and width
// Fills matrix with random integers
void fillMatrix(vector <vector <int> > &input, int n)
{
	int max_random = floor(sqrt(INT_MAX / n));
	int newNum;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			input[i][j] = rand() % max_random;
		}
	}
}