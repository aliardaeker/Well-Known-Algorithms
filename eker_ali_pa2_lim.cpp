/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 2:
	Large Integer Multiplication
	10.19.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <math.h>       /* pow, floor */
#include <algorithm>	/* max */

using namespace std;

// Return: number of inputs
// Parameters: none
// Prompts user and validate the input
int takeUserInput();

// Return: double typed random number
// Param 1: how many digits the random number should be
// Generate a large random integer
double generateRandomInt(int digit);

// Return: how many digits a number has
// Param: input number to count its digits
// Counts how many digit the given number has
int numDigits(long u);

// Return: Result of the product
// Param 1: large number 1
// Param 2: large number 2
// Multiplies 2 large number by cutting them half at each call
double largeIntegerProduct(double u, double v);

// Return: Result of the product
// Param 1: large number 1
// Param 2: large number 2
// Multiplies 2 large number by cutting them one third at each call
double LIP2(double u, double v);

// Main function: starting point of the program
int main ()
{
	srand(time(NULL));
	int n = takeUserInput();

	double a = generateRandomInt(n);
	double b = generateRandomInt(n);

	cout << "\nRandom Number 1: " << a;
	cout << "\nRandom Number 2: " << b;

	cout << "\n\nNormal Multiplication:\n";
	cout << a * b << "\n\n";

	cout << "Original Large Integer Multiplication:\n";
	double res = largeIntegerProduct(a, b);
	cout << res << "\n\n";

	cout << "Updated Large Integer Multiplication:\n";
	res = LIP2(a, b);
	cout << res << "\n\n";
}

// Return: Result of the product
// Param 1: large number 1
// Param 2: large number 2
// Multiplies 2 large number by cutting them half at each call
double largeIntegerProduct(double u, double v)
{
	double x, y, w, z;
	int n, m;

	// The number of digits of the bigger number
	n = max(numDigits(u), numDigits(v));

	// If number is 0 just return 0
	if (u == 0 || v == 0) return 0;
	// If 1 digit left, do the normal multiplication
	else if (n == 1) return u * v;
	else
	{
		// Cut in half
		m = floor(n / 2);

		// Take each digit in each half
		x = floor(u / pow(10, m));
		y = u - (x * pow(10, m));

		w = floor(v / pow(10, m));
		z = v - (w * pow(10, m));

		// Recursively do the same thing until we had just 1 digit left
		return largeIntegerProduct(x, w) * pow(10, 2 * m) +
			   (largeIntegerProduct(x, z) + largeIntegerProduct(w, y)) *
			   pow(10, m) + largeIntegerProduct(y, z);
	}
}

// Return: Result of the product
// Param 1: large number 1
// Param 2: large number 2
// Multiplies 2 large number by cutting them one third at each call
// Updated large integer multiplication
double LIP2(double u, double v)
{
	double u1, u2, u3, v1, v2, v3;
	double a1, a2, a3, a4, a5;
	int n, m;

	// These parts are similar to the original algorithm
	n = max(numDigits(u), numDigits(v));

	if (u == 0 || v == 0) return 0;
	else if (n <= 2) return u * v;
	else
	{
		// Cut in three
		m = floor(n / 3);

		// Devide first number into 3 digits
		u1 = floor(u / pow(10, 2 * m));
		u2 = floor((u - (u1 * pow(10, 2 * m))) / pow(10, m));
		u3 = u - (u1 * pow(10, 2 * m) + u2 * pow(10, m));

		// Devide second number into 3 digits
		v1 = floor(v / pow(10, 2 * m));
		v2 = floor((v - (v1 * pow(10, 2 * m))) / pow(10, m));
		v3 = v - (v1 * pow(10, 2 * m) + v2 * pow(10, m));

		// Do the multiplication based on each digit`s base
		// and continue this until we have 2 or less digits left
		a1 = LIP2(u1, v1) * pow(10, 4 * m);
		a2 = (LIP2(u1, v2) + LIP2(v1, u2))  * pow(10, 3 * m);
		a3 = (LIP2(u1, v3) + LIP2(v1, u3) + LIP2(v2, u2))  * pow(10, 2 * m);
		a4 = (LIP2(u2, v3) + LIP2(v2, u3))  * pow(10, 1 * m);
		a4 = LIP2(u3, v3);

		return a1 + a2 + a3 + a4 + a5;
	}
}

// Return: how many digits a number has
// Param: input number to count its digits
// Counts how many digit the given number has
int numDigits(long u)
{
	int counter = 0;

	while (u)
	{
		u /= 10;
		counter++;
	}

	return counter;
}

// Return: double typed random number
// Param 1: how many digits the random number should be
// Generate a large random integer
double generateRandomInt(int digit)
{
	double num = 0;

	for (int i = 0; i < (digit - 1); i++)
	{
		num = num + (rand() % 10) * pow(10, i);
	}

	// We want the last digit not to be 0
	num = num + ((rand() % 9) + 1) * pow(10, digit - 1);

	return num;
}

// Return: number of inputs
// Parameters: none
// Prompts user and validate the input
int takeUserInput()
{
	cout << "\nEnter n = 6k where k is a positive integer.\n";

	bool flag = true;
	int n, k;

	while (flag)
	{
		flag = false;
		cin >> n;

		// Checks if input is valid
		if (n < 6 || cin.fail())
		{
			cout << "Invalid input !!! n = 6k where k is a positive integer !!!\nEnter again: ";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}

		k = n % 6;

		if (k != 0 && flag == false)
		{
			cout << "Invalid input !!! n = 6k where k is a positive integer !!!\nEnter again: ";
			flag = true;
			cin.clear();
			cin.ignore(256,'\n');
		}
	}

	return n;
}