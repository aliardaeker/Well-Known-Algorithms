/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 5: Knapsack Problem
		Solved by brute force, refined dynamic
	programming and backtracking using pruned 
	state space tree with fractional knapsack
	12.05.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <math.h>       /* floor */
#include <math.h>       /* pow */
#include <algorithm>    /* max */
#include <iomanip>		/* setw */
#include <vector>		/* vector */

using namespace std;

// Item to fill knapsack with.
// Profit is the value, id is used for printing
struct item 
{
	int profit;
	int weight;
	int id;
};

// Node which defines every way in backtracking
struct node
{
	int profit;
	int weight;
	int level;
};

// Knapsack which has item array, total weight and profit
struct knapsack
{
	item items[8];

	int num_item;
	int total_weight;
	int total_profit;
};

// To do refinement in dynamic program
// Items which calculate flag is flas is nor needed for result
struct tableItem
{
	int value;
	bool calculate_flag;
};

// Brute force method, takes item list total capacity and number of items.
void bruteForce (item * list, int capacity, int size);

// Utility function for brute force.
// Takes array consist of booleans and its length. Convert it do decimal
// then add one and then convert back to binary form to traverse all
// possible combinations
void bits_add_one (bool * bit_array, int length);

// Dynamic programming approach, takes item array, total capacity and 
// number of items.
void dynamicApproachRefined (item * list, int capacity, int size);

// Backtrack algorithm, takes total capacity and number of items
void backtrack (item * list, int capacity, int size);

// Utility functions of backtrack algorithm
// Sort the item list by the order of profit / weight
void sort (item list[], int size);

// Fractional knapsack problem is used to define bound per node.
// Takes node`s level, its profit, weight, item list, total capacity and number of items
// to return upper bound.
int kwf2 (int depth, int v_profit, int v_weight, item list[], int capacity, int size);

// Calls kwf2 to decide if a node is promissing or not. Returns true if promissing
// returns false if not promissing.
bool promising (int level, int p, int w, item list[], int capacity, int size);

// Global to hold maximum profit calculated so far for backtracking 
int max_profit;

// Starting point of the program
int main ()
{
	srand(time(NULL));
	int n = (rand() % 5) + 4;
	cout << "\nNumber of items: " << n << "\n";

	item item_list[n];
	int i, knapsack_capacity, total_weight = 0;

	// Randomly creating and printing the items
	for (i = 0; i < n; i++)
	{
		item it;
		it.id = i;
		it.profit = (rand() % 21) + 10;
		it.weight = (rand() % 16) + 5;
		
		item_list[i] = it;
		total_weight = total_weight + it.weight;

		cout << "  --> Item " << it.id << ": W(" << it.weight << ") P(" << it.profit << ")\n";
	}
	
	knapsack_capacity = floor(0.6 * total_weight);
	cout << "Knapsack Capacity: " << knapsack_capacity; 
	cout << "\n\n-----------------------------";

	cout << "\n\nBrute Force:\n";
	bruteForce(item_list, knapsack_capacity, n);
	cout << "\n-----------------------------\n";

	cout << "\nDynamic Approach:\n\n";
	dynamicApproachRefined(item_list, knapsack_capacity, n);
	cout << "-----------------------------\n";

	cout << "\nBacktracking Algorithm:\n\n";
	backtrack(item_list, knapsack_capacity, n);
}

// Backtrack algorithm to solce knapsack problem
// Takes the items list, total capacity of the knapsack and number of items
void backtrack(item * list, int capacity, int size)
{
	// First sort the items for kwf2 to work correctly
	sort(list, size);
	vector <node> bestset;
	vector <int> item_id_holder;

	max_profit = 0;
	node u, v;
	u.level = -1;
	v.level = 0;
	u.profit = 0;
	u.weight = 0;
	bestset.push_back(u);
	int bound, node_counter = 0, weight = 0, i, j;
	cout << "Node information in the traversed order of pruned space tree:\n";	

	// Until we traverse all promissing nodes
	while (!bestset.empty())
	{
		// Pop from front
		u = bestset.front();
		bestset.erase(bestset.begin());
		
		// Loops if we are at the last level 
		if (u.level == size - 1) continue;

		v.level = u.level + 1;
		v.weight = u.weight + list[v.level].weight;
		v.profit = u.profit + list[v.level].profit;

		// If we are under capacity and profit is more than the max profit update max profit
		if (v.weight <= capacity && v.profit > max_profit) 
		{
			// Calculating bond per node
			bound = kwf2(v.level, v.profit, v.weight, list, capacity, size);
			cout << "  --> Node " << node_counter << ": W(" << v.weight << ") P(" << v.profit << ") B(" << bound << ")\n";
			node_counter++;

			// This is for printing later
			item_id_holder.push_back(list[v.level].id);
			max_profit = v.profit;
			weight = v.weight;
		}

		// If promissing take it for the consideration
		if (promising(v.level, v.profit, v.weight, list, capacity, size)) bestset.push_back(v);

		// If other node at the same level is also promising take it as consideration too 
		v.weight = u.weight;
		v.profit = u.profit;
		if (promising(v.level, v.profit, v.weight, list, capacity, size)) bestset.push_back(v);
	}

	cout << "\nTotal Weight: " << weight << "\n";
	cout << "Total Profit: " << max_profit << "\n\n";
	cout << "Items taken: " << "\n";

	for (i = 0; i < size; i++)
	{
		item it = list[i];

		for (j = 0; j < item_id_holder.size(); j++)
		{
			if (it.id == item_id_holder[j]) cout << "  --> Item " << it.id << ": W(" << it.weight << ") P(" << it.profit << ")\n";
		}
	}
	cout << "\n";
}

// Knapsack with fraction problem returns the upper bound for backtracing
int kwf2(int i, int v_profit, int v_weight, item list[], int capacity, int size)
{
	// I capacity is exceeded, just returns
	if (v_weight > capacity) return 0;

	int bound = v_profit; 

	// Until capacity is exceeded take items and increment the bound with their profit
	while (i < size && (v_weight + list[i].weight <= capacity))
	{
		v_weight = v_weight + list[i].weight;
		bound = bound + list[i].profit;
		i++;
	}

	// Fractional part
	if (i < size) bound = bound + (capacity - v_weight) * list[i].profit / list[i].weight;

	return bound;
}

// Used for deceding if a node should be considered for benefit
bool promising(int level, int p, int w, item list[], int capacity, int size)
{
	if (w > capacity) return false;

	// Bound is retrived 
	int bound = kwf2(level, p, w, list, capacity, size);

	// If bound is more than max profit return true otherwise return false
	if (bound > max_profit) return true;
	else return false;
}

// Sort the items according the profit / weight
void sort(item list[], int size)
{
	int i, j;
	double p_div_w_i, p_div_w_j;

	// Insertion sort
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			p_div_w_i = list[i].profit / (double) list[i].weight;
			p_div_w_j = list[j].profit / (double) list[j].weight;

			if (p_div_w_i > p_div_w_j)
			{
				// Swapping
				item tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}

// Refined Dynamic Approach, takes list of items, total capacity and number of items
void dynamicApproachRefined (item * list, int capacity, int size)
{
	tableItem table[size + 1][capacity + 1];
	int i, j, range = 1;
	int datas[1000], tmp[1000], tmp_counter = 0;
	int w_index1, w_index2, k;
	bool not_found = true;

	knapsack bag;
	bag.num_item = 0;
	bag.total_weight = 0;
	bag.total_profit = 0;

	datas[0] = capacity;

	// Initialize table
	for (i = 0; i < size + 1; i++)
	{
		for (j = 0; j < capacity + 1; j++)
		{
			table[i][j].value = 0;
			table[i][j].calculate_flag = false;
		}
	}

	// Decide which cells are needed for final result,
	// Mark them as true, others left false
	for (i = size; i > 0; i--)
	{
		for (j = 0; j < range; j++) table[i][datas[j]].calculate_flag = true;

		for (k = 0; k < range; k++)
		{
			w_index1 = datas[k];
			w_index2 = datas[k] - list[i - 1].weight;

			tmp[k * 2] = w_index1;
			tmp[(k * 2) + 1] = w_index2;
			tmp_counter = k * 2 + 1;
		}

		for (k = 0; k <= tmp_counter; k++) datas[k] = tmp[k];

		range = range * 2;
	}

	// Dynamic programming takes place here
	for (i = 0; i <= size; i++)
	{
		for (j = 0; j <= capacity; j++)
		{
			if (i == 0 || j == 0) table[i][j].value = 0;
			// Only consider the previously true marked cells for final result
			else if (table[i][j].calculate_flag == true)
			{
				if (list[i - 1].weight <= j) 
				{
					item it = list[i - 1];
					table[i][j].value = max(it.profit + table[i - 1][j - it.weight].value, table[i - 1][j].value); 
				}
				else table[i][j].value = table[i - 1][j].value;
			}
		}

		for (j = 0; j <= capacity; j++) cout << table[i][j].value << setw(3);
		cout << "\n";
	}

	j = capacity;
	i = size;
	int w, total_weight = 0;

	// This is for finding the items used.
	while (i > 0)
	{
		item it = list[i - 1];
		w = it.weight;

		if (table[i][j].value - table[i - 1][j - w].value == it.profit)
		{
			bag.items[bag.num_item] = it;
			bag.num_item++;
			total_weight = total_weight + w;

			i--;
			j = j - w;
		}
		else i--;
	}

	cout << "\nTotal Weight: " << total_weight << "\n";
	cout << "Total Profit: " << table[size][capacity].value << "\n";

	for (i = 0; i < bag.num_item; i++)
	{
		item it = bag.items[i];
		cout << "  --> Item " << it.id << ": W(" << it.weight << ") P(" << it.profit << ")\n";
	}
	cout << "\n";
}

// Tries all possible combinations to find the best solutions
void bruteForce (item * list, int capacity, int size)
{
	int all_combinations = pow(2.0, size);
	int i, j, max_profit = 0, found_index;

	bool bits[size];
	knapsack all_subsets[all_combinations];

	for (i = 0; i < size; i++) bits[i] = false;

	for (i = 0; i < all_combinations; i++)
	{
		// Initialize a new knapsack for each possible solution
		// Later discard the ones which exceed the capacity
		knapsack k;
		k.total_weight = 0;
		k.total_profit = 0;
		k.num_item = 0;

		for (j = 0; j < size; j++)
		{
			// Bits represent which computations are tried already
			if (bits[j] == true)
			{
				item i = list[j];
				
				k.total_weight = k.total_weight + i.weight;
				k.total_profit = k.total_profit + i.profit;
			
				k.items[k.num_item] = i;
				k.num_item++;
			}
		}

		// Until last loop, add 1 to the binary bits
		// This is ensuring we try all possible solutions
		if (i != all_combinations - 1) bits_add_one(bits, size);

		// If the capacity is exceeded just make its profit 0 
		// so that it cannot be the final result
		if (k.total_weight > capacity) k.total_profit = 0; 
	
		all_subsets[i] = k;
	}

	// Choose the one with the highest profit
	for (i = 0; i < all_combinations; i++)
	{
		if (all_subsets[i].total_profit > max_profit)
		{
			max_profit = all_subsets[i].total_profit;
			found_index = i;
		}
	}

	// Printing
	if (max_profit == 0) cout << "\nKnapsack has no item.";
	else
	{
		cout << "\nTotal Weight: " << all_subsets[found_index].total_weight;
		cout << "\nTotal Profit: " << all_subsets[found_index].total_profit << "\n";

		for (i = 0; i < all_subsets[found_index].num_item; i++)
		{
			item it = all_subsets[found_index].items[i];
			cout << "  --> Item " << it.id << ": W(" << it.weight << ") P(" << it.profit << ")\n";
		}
	}
}

// Takes a boolean array and its length
void bits_add_one (bool * bit_array, int length)
{
	int total = 0, i, value;

	// Converts the boolean array which represent a binary number to decimal
	for (i = 0; i < length; i++)
	{
		if (bit_array[length - i - 1] == true)
		{
			total = total + pow(2.0, i);
		}
	}

	// Increments the decimal by 1
	total++;

	// Convert the decimal back to binary
	for (i = 0; i < length; i++)
	{
		value = pow(2.0, length - i - 1);

		if (value <= total)
		{
			total = total - value;
			bit_array[i] = true;
		}
		else bit_array[i] = false;
	}

	if (total != 0) cout << "\nERROR IN bits_add_one !!! Total: " << total;
}