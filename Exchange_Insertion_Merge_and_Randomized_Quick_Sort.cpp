/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 1
	10.3.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <vector>		/* vector */
#include <math.h>       /* floor */

using namespace std;

// Global Values: 
// Selected type of the sorting algorithm
float algo;
// Used in insertion and exchange sort to hold values
vector <int> vectorToSort;
// Maximum number that can be assigned as key
int MAX_NUM_VALUE = 1000;
// Total number ofkeys
int N;

// Parameters: none
// Return: int to indicate the input size
// Prompt user to choose the sorting algorithm and input size
int takeUserInput();

// Parameters: int to indicate input size
// Return: none
// Performing exchange sort
void exchangeSort(int n);

// Parameters: int to indicate input size
// Return: none
// Performing insertion sort
void insertionSort(int n);

// Parameters: 
// 1) int to indicate input size
// 2) int array to be sorted
// Return: none
// Dividing array into 2 parts
void mergeSort(int n, int arr[]);

// Parameters: 
// 1) int to indicate the length of sub array u
// 2) int to indicate the length of sub array v
// 3) int sub array to be combined after comparion 
// 4) int sub array to be combined after comparison
// 5) int main array to be sorted
// Return: none
// Merging 2 given sub array after comparison
void merge(int h, int m, int u[], int v[], int s[]);

// Parameters: 
// 1) int array to be sorted
// 2) int to indicate the low index
// 3) int to indicate the high index 
// Return: none
// Performing quick sort with a randomly choosen pivot
void randomizedQuickSort(int arr[], int l, int r);

// Parameters: int to indicate input size
// Return: none
// Generate array with random numbers
void generateRandomNumbers(int n);

// Parameters: none
// Return: none
// Printing starts in random vector to show user
void visualize();

// Parameters: 
// 1) int array to show user
// 2) int to indicate input size
// Return: none
// Printing starts in random array to show user
void visualizeArray(int arr [], int length);

// Main function: starting point of the program
int main ()
{
	int i;
	int inputSize = takeUserInput();
	generateRandomNumbers(inputSize);

	// Exchange sort
	if (algo == 1) 
	{
		if (inputSize <= 20) visualize();
		exchangeSort(inputSize);
	}
	// Insertion sort
	else if (algo == 2) 
	{
		if (inputSize <= 20) visualize();
		insertionSort(inputSize);
	}
	// Merge sort
	else if (algo == 3) 
	{
		cout << "\n";
		int inputArray[inputSize];
		// Copy from vector to array
		for (i = 0; i < inputSize; i++) inputArray[i] = vectorToSort.at(i);
		N = inputSize;
		mergeSort(inputSize, inputArray);

		cout << "Sorted by Merge Sort:\n[ ";
		// Print the sorted array
		for (i = 0; i < inputSize; i++) cout << inputArray[i] << " ";
		cout << "]\n";
	}
	// Randomized quick sort
	else if (algo == 4) 
	{
		cout << "\n";
		int inputArray[inputSize];
		// Copy from vector to array
		for (i = 0; i < inputSize; i++) inputArray[i] = vectorToSort.at(i);

		N = inputSize;
		if (N <= 20) visualizeArray(inputArray, N);
		randomizedQuickSort(inputArray, 0, inputSize);

		cout << "Sorted by Randomized Quick Sort:\n[ ";
		// Print the sorted array
		for (i = 0; i < inputSize; i++) cout << inputArray[i] << " ";
		cout << "]\n";
	}
	else cout << "!!! ERROR IN ALGO VALUE !!!";
}

// Parameters: none
// Return: int to indicate the input size
// Prompt user to choose the sorting algorithm and input size
int takeUserInput()
{
	cout << "\nChoose your favorite sorting algorithm !\n";
	cout << "(Press `1`, `2`, `3` or `4` to choose)\n\n";
	cout << "	1) Exchange Sort\n";
	cout << "	2) Insertion Sort\n";
	cout << "	3) Merge Sort\n";
	cout << "	4) Randomized Quick Sort\n";

	bool flag = true;
	float n;

	// Loops until user enters a valid agorithm type
	while (flag)
	{
		flag = false;
		cin >> algo;

		// Checks if input is valid
		if ((algo != 1 && algo != 2 && algo != 3 && algo != 4) || cin.fail())
		{
			cout << "Invalid input !!! Press 1, 2, 3 or 4 !!!\n";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}
	}

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

// Parameters: int to indicate input size
// Return: none
// Generate array with random numbers
void generateRandomNumbers(int n)
{
	srand(time(NULL));
	int newNum, i;

	// If user input is less than 20, max key value is 15
	if (n <= 20) MAX_NUM_VALUE = 15;

	cout << "\nRandom Input Array:\n[ ";
	// Generating and printing the random array
	for (i = 0; i < n; i++)
	{
		newNum = rand() % MAX_NUM_VALUE;
		cout << newNum << " ";
		vectorToSort.push_back(newNum);
	}
	cout << "]\n";
}

// Parameters: none
// Return: none
// Printing starts in random vector to show user
void visualize()
{
	int i, j;

	cout << "\n";
	// Traverses the random vector to be sorted
	for (i = 0; i < vectorToSort.size(); i++)
	{
		if (vectorToSort.at(i) == 0) cout << "-";
		else for (j = 0; j < vectorToSort.at(i); j++) cout << "* ";
		cout << "\n";
	}
}

// Parameters: 
// 1) int array to show user
// 2) int to indicate input size
// Return: none
// Printing starts in random array to show user
void visualizeArray(int arr [], int length)
{
	int i, j;

	// Traverses the random array to be sorted
	for (i = 0; i < length; i++)
	{
		if (arr[i] == 0) cout << "-";
		else for (j = 0; j < arr[i]; j++) cout << "* ";
		cout << "\n";
	}
	cout << "\n";
}

// Parameters: int to indicate input size
// Return: none
// Performing exchange sort
void exchangeSort(int n)
{
	int tmp, i, j;

	// Traverses the array 
	for(i = 0; i < (n - 1); i++)
	{
		// For each key compare it with others
		for (j = (i + 1); j < n; j++)
		{
			// Swapping if the selected key is bigger
			if (vectorToSort.at(i) > vectorToSort.at(j))
			{
				tmp = vectorToSort.at(i);
				vectorToSort.at(i) = vectorToSort.at(j);
				vectorToSort.at(j) = tmp;
			}

			// Printing the array after each step
			if (n <= 20) visualize();
		}
	}

	cout << "\nSorted by Exchange Sort:\n[ ";
	// Printing the sorted version of the array
	for (i = 0; i < n; i++) cout << vectorToSort.at(i) << " ";
	cout << "]\n";
}

// Parameters: int to indicate input size
// Return: none
// Performing insertion sort
void insertionSort(int n)
{
	int i, j, key;

	// Traverses the array
	for(i = 1; i < n; i++)
	{
		key = vectorToSort.at(i);
		// For each key makes the comparison
		for (j = (i - 1); (j >= 0) && (vectorToSort.at(j) > key); j--) vectorToSort.at(j + 1) = vectorToSort.at(j);

		vectorToSort.at(j + 1) = key;
		// Printing the array after each step
		if (n <= 20) visualize();
	}

	cout << "\nSorted by Insertion Sort:\n[ ";
	// Printing the sorted version of the array
	for (i = 0; i < n; i++) cout << vectorToSort.at(i) << " ";
	cout << "]\n";
}

// Parameters: 
// 1) int to indicate input size
// 2) int array to be sorted
// Return: none
// Dividing array into 2 parts
void mergeSort(int n, int arr[])
{
	int tmp[n];
    int m, i;

    // If the size is less than 2 just return
    if (n < 2) 
    {
    	// Visualizing last step
    	if (N <= 20) visualizeArray(arr, n);
    	return;
    }
    else 
    {
    	// Visualing each step
		//if (N <= 20) visualizeArray(arr, n);

     	m = n / 2;
     	// Recursive calls for each half
        mergeSort(m, arr);
        mergeSort(n - m, arr + m);
        // Merging the sorted sub parts
        merge (m, n - m, arr, arr + m, tmp);
        for (i = 0; i < n; i++) arr[i] = tmp[i];

        if (N <= 20) visualizeArray(arr, n);
    }
}

// Parameters: 
// 1) int to indicate the length of sub array u
// 2) int to indicate the length of sub array v
// 3) int sub array to be combined after comparion 
// 4) int sub array to be combined after comparison
// 5) int main array to be sorted
// Return: none
// Merging 2 given sub array after comparison
void merge(int h, int m, int u[], int v[], int s[])
{
	int i = 0, j = 0, k = 0, z;

	// Traverses each sub array
	while (i < h && j < m)
	{
		// Comparison 
		if (u[i] < v[j]) s[k++] = u[i++];
		else s[k++] = v[j++];
	}

	// Combining on the input array
	while (i < h) s[k++] = u[i++];   
    while (j < m) s[k++] = v[j++];   
}

// Parameters: 
// 1) int array to be sorted
// 2) int to indicate the low index
// 3) int to indicate the high index 
// Return: none
// Performing quick sort with a randomly choosen pivot
void randomizedQuickSort(int arr[], int l, int r)
{
	int left = l;
    int right = r - 1;
    int length = r - l, tmp;

    if (length > 1) 
    {
    	// Randomly chooses pivot
        int pivot = arr[rand() % length + left];

        // If we have an array to sort
        while (left < right) 
        {
        	// Comparison based on the pivot
            while (arr[right] > pivot && right > left) right--;
            while (arr[left] < pivot && left <= right) left++;

            // Swapping each key
            if (left < right) 
            {
            	tmp = arr[left];
            	arr[left] = arr[right];
            	arr[right] = tmp;
                left++;
            }
        }  

        // Recursive calls for each hals
        randomizedQuickSort(arr, l, left);
        randomizedQuickSort(arr, right, r);
        // Visualize each step
        if (N <= 20) visualizeArray(arr, N);
    }
}