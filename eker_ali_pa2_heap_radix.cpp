/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 2:
	Heap & Radix Sort
	10.19.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <math.h>       /* pow, floor */

using namespace std;
int MAX_NUM_VALUE = 10000;

// Return: int to indicate number of inputs
// Param 1: pointer to a integer. 1 for heap, 2 for radix
// Takes user input and validates
int takeUserInput(int &a);

// Return: void
// Param 1: number of inputs
// Param 2: algorithm type
// Param 3: input array
// Generate random number of arrays up to algorithm type
void generateRandomNumbers(int n, int algo, int A[]);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Calls Build heap sort and then heap sort functions
void HeapSortBase(int A[], int n);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Builds the max heap with given random array
void BuildMaxHeap(int A[], int n);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Sorts the max heap
void HeapSort(int A[], int n);

// Return: void
// Param 1: input array
// Param 2: current element to be compared 
// Param 3: number of inputs
// Keeps the heap structure after every swap
void MaxHeapify(int A[], int i, int n);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Sorts input array with radix sort
void RadixSort(int A[], int n);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Param 3: the digit number that is going to be sorted
void CountSort(int A[], int n, int digit);

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Printing starts if n is less than 20
void visualizeArray(int A[], int n);

// Main function: starting point of the program
int main ()
{
	srand(time(NULL));
	int algo;
	int n = takeUserInput(algo);

	int arrayToSort[n];
	generateRandomNumbers(n, algo, arrayToSort);

	if (n <= 20) visualizeArray(arrayToSort, n);

	if (algo == 1) HeapSortBase(arrayToSort, n);
	else RadixSort(arrayToSort, n);

	cout << "\nSorted Array:\n[ ";
	for (int i = 0; i < n; i++) cout << arrayToSort[i] << " ";
	cout << "]\n\n";
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Printing starts if n is less than 20
void visualizeArray(int A[], int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		if (A[i] == 0) cout << "-";
		else for (j = 0; j < A[i]; j++) cout << "* ";
		cout << "\n";
	}
	cout << "\n";
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Param 3: the digit number that is going to be sorted
void CountSort(int A[], int n, int digit)
{
	int i;
	int counter[10] = {0};
	int result[n];

	// Counts the number of appearances
	for (i = 0; i < n; i++) counter[((int) floor(A[i] / pow(10, digit))) % 10]++;

	// We need this to understand which one comes first
	for (i = 1; i < 10; i++) counter[i] += counter[i - 1];

	// We traverse the number of appearances and put each element based on 
	// its number of appearances to the output array 
	for (i = n - 1; i >= 0; i--)
    {
        result[counter[((int) floor(A[i] / pow(10, digit))) % 10] - 1] = A[i];
        counter[((int) floor(A[i] / pow(10, digit))) % 10 ]--;
    }

    // Update input array
    for (i = 0; i < n; i++) A[i] = result[i];
    if (n <= 20) visualizeArray(A, n);	
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Sorts input array with radix sort
void RadixSort(int A[], int n)
{
	// Calls counting sort for each digit
	for (int i = 0; i < 3; i++)
	{
		CountSort(A, n, i);
	}
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Sorts the max heap
void HeapSort(int A[], int n)
{
    int i, tmp;

    for (i = n - 1; i >= 0; i--)
    {
    	// Swap the first with the last element
        tmp = A[i];
        A[i] = A[0];
        A[0] = tmp;
        if (n <= 20) visualizeArray(A, n);

        // Keeps heap property 
        MaxHeapify(A, 0, i);
    }
}

// Return: void
// Param 1: input array
// Param 2: current element to be compared 
// Param 3: number of inputs
// Keeps the heap structure after every swap
void MaxHeapify(int A[], int i, int n)
{
	int largest, tmp;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If the left child is bigger than its parent
    if (left < n && A[left] > A[i]) largest = left;
    else largest = i;

    // If the right child is bigger than its parent
    if (right < n && A[right] > A[largest]) largest = right;

    if(largest != i)
    {
    	// Moves down in the heap tree
         tmp = A[i];
         A[i] = A[largest];
         A[largest] = tmp;
         MaxHeapify(A, largest, n);
    }
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Builds the max heap with given random array
void BuildMaxHeap(int A[], int n)
{
	int i;
	// Builds a tree that each parent is bigger than its children
	for(i = floor(n / 2); i >= 0; i--) MaxHeapify(A, i, n);
	if (n <= 20) visualizeArray(A, n);
}

// Return: void
// Param 1: input array
// Param 2: number of inputs
// Calls Build heap sort and then heap sort functions
void HeapSortBase(int A[], int n)
{
	BuildMaxHeap(A, n);
	HeapSort(A, n);
}

// Return: int to indicate number of inputs
// Param 1: pointer to a integer. 1 for heap, 2 for radix
// Takes user input and validates
int takeUserInput(int &a)
{
	cout << "\nChoose your favorite sorting algorithm !\n";
	cout << "(Press `1` or `2` to choose)\n\n";
	cout << "	1) Heap Sort\n";
	cout << "	2) Radix Sort\n";

	bool flag = true;
	int algo, n;

	// Loops until user enters a valid agorithm type
	while (flag)
	{
		flag = false;
		cin >> algo;

		// Checks if input is valid
		if ((algo != 1 && algo != 2) || cin.fail())
		{
			cout << "Invalid input !!! Press `1` or `2` !!!\n";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}
	}

	a = algo;
	flag = true;
	cout << "\nEnter your best input size from 1 to 1000 !\n";

	// Loops until user enters a valid input size
	while (flag)
	{
		flag = false;
		cin >> n;

		// Checks if input is valid
		if (cin.fail() || n < 1 || n > 1000 || (n - (int) (n / 1) > 0))
		{
			cout << "Invalid input !!! Enter a number between 1 and 1000 !!!\n";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}
	}

	return n;
}

// Return: void
// Param 1: number of inputs
// Param 2: algorithm type
// Param 3: input array
// Generate random number of arrays up to algorithm type
void generateRandomNumbers(int n, int algo, int A[])
{
	int newNum, i;

	// If user input is less than 20, max key value is 15
	if (n <= 20) MAX_NUM_VALUE = 16;
	else if (algo == 2) MAX_NUM_VALUE = 1000;

	cout << "\nRandom Input Array:\n[ ";
	// Generating and printing the random array
	for (i = 0; i < n; i++)
	{
		newNum = rand() % MAX_NUM_VALUE;
		cout << newNum << " ";
		A[i] = newNum;
	}
	cout << "]\n\n";
}