/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 3:
	Floyd`s Algorithm to find shortest path
	11.07.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <iomanip>		/* setw */

using namespace std;

// return: void
// Generates a random matrix and calculates shortest path for each pair
void floyd();

// Main function: starting point of the program
int main ()
{
	srand(time(NULL));
	floyd();
}

// return: void
// Generates a random matrix and calculates shortest path for each pair
void floyd()
{
	int n =  (rand() % 6) + 5;
	int adjacencyMatrix[n][n], pathMatrix[n][n];
	int num, i, j, k;
	cout << "\nAdjacency Matrix: \n\n";

	// PathMatrix will be used to hold vertexes to be scanned in order to get shortest path
	for (i = 0; i < n; i++)	for (j = 0; j < n; j++) pathMatrix[i][j] = 0;

	// Fills the half of the initial matrix
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i >= j) adjacencyMatrix[i][j] = 0;
			else 
			{
				num = (rand() % 10) + 1;
				adjacencyMatrix[i][j] = num;
			}
		}
	}

	// Fills the other half with the same values.
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i < j) adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
		}
	}

	// Prints initial values
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << setw(2) << adjacencyMatrix[i][j] << "  ";
		}
		cout << "\n";
	}

	// Iteration counter
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				// If the sum is less than the actual value we update it and mark the pathMatrix
				if (adjacencyMatrix[j][i] + adjacencyMatrix[i][k] < adjacencyMatrix[j][k])
				{
					adjacencyMatrix[j][k] = adjacencyMatrix[j][i] + adjacencyMatrix[i][k];
					pathMatrix[j][k] = i + 1;
				}
			}
		}
	}

	cout << "\nAll pairs shortest path lengths:\n\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << setw(2) << adjacencyMatrix[i][j] << "  ";
		}
		cout << "\n";
	}

	cout << "\nAll pairs shortest paths:\n\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << setw(2) << pathMatrix[i][j] << "  ";
		}
		cout << "\n";
	}
	cout << "\n";
}