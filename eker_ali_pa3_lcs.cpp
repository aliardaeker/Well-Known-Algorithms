/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 3:
	Longest Common Subsequence Algorithm using Dynamic Programming
	11.07.17	
*/

#include <iostream>		/* cout, cin */
#include <algorithm>	/* max */

using namespace std;

// return: int to indicate length of longest sequence
// param 1: first input string
// param 2: second input string
// Calculates the length of the longest common subsequence using Dynamic Programing 
int lcs (string input1, string input2);

// Main function: starting point of the program
int main (int argc, char * argv[])
{
	// Checks if 2 command input given
	if (argc == 3)
	{
		string str1 = argv[1]; 
		string str2 = argv[2];

		// Inputs should be less than 100 in size
		if (str1.length() > 100 || str2.length() > 100) cout << "\nEach string should be at most 100 characters !!!\n\n";
		else 
		{
			int result = lcs(str1, str2);
			cout << "\nLongest Common Subsequence between " << str1 << " and " << str2 << " has lentgh " <<  result << ".\n\n";
		}
	}
	else cout << "\n2 strings needed !!!\n\n";
}

// return: int to indicate length of longest sequence
// param 1: first input string
// param 2: second input string
// Calculates the length of the longest common subsequence using Dynamic Programing 
int lcs (string input1, string input2)
{
	int length1 = input1.length();
	int length2 = input2.length();

	// Double array to be used for dynamic programing
	int resultTable[length1 + 1][length2 + 1];
	int i, j;

	for (i = 0; i <= length1; i++)
	{
		for (j = 0; j <= length2; j++)
		{
			// If either of the values is 0, just assign 0
			if (i == 0 || j == 0) resultTable[i][j] = 0;
			// If characters match, used previously calculated values from the table
			else if (input1[i - 1] == input2[j - 1]) resultTable[i][j] = 1 + resultTable[i - 1][j - 1];
			// If dont match take the maximum of of left or upper value from the table
			else resultTable[i][j] = max(resultTable[i - 1][j], resultTable[i][j - 1]);
		}
	}

	return resultTable[length1][length2];
}