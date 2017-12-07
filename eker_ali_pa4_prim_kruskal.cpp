/*  
	Ali Arda Eker
	Design & Analysis of Computer Algorithms
	CS 575 - FALL 17
	Programming Assignment 4:
		Imlementation of Prim`s and Kruskal`s Minimum Spanning Tree algorithms. For Prim`s 
	algorithm, a priority queue is used to hold vertices and array for data structure. For
	Kruskal`s algorithm, again arrays are used for data structures. Find3() method also does
	compression and Union3() method is modified to support this in order to improve run time.
	11.21.17	
*/

#include <iostream>		/* cout, cin */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <stdio.h>	    /* NULL */
#include <iomanip>		/* setw */
#include <climits>		/* INT_MAX */

using namespace std;

// Vertex structure consist of its id,
// parent`s id and a cost (for Prim)
struct vertex 
{
	int id;
	int cost; // this is used as height in kruskal algorithm
	int parentId;
};

// Edge structure to indicate the vertex ids
// which share an edge and its weight.
struct edge 
{
	int vertex_id_1;
	int vertex_id_2;
	int weight;
};

// return: 1 for Prim, 2 for Kruskal
// Prompts user to take input
int promptUser ();

// param 1: adjacency matrix
// param 2: size of a single dimension
// Perform Prim`s MST algorithm
void prim (int ** matrix, int size);

// Utility functions for Prim`s MST
void sort(vertex priorityQueue[], int size);
bool _include(vertex priorityQueue[], int vertexToFind, int sizeOfQueue);
int getCost(vertex queue[], int vertexId, int size);
void setCost(vertex queue[], int vertexId, int weight, int size);
void setParentId(vertex queue[], int vertexId, int idToSet, int size);

// param 1: adjacency matrix
// param 2: size of a single dimension
// Perform Kruskal`s MST algorithm
void kruskal (int ** matrix, int size);

// Utility functions for Kruskal`s MST
int find3(vertex set[], int i);
void union3(vertex set[], int i, int j);
void sortEdges(edge edges[], int size);

// Starting point of the program
int main ()
{
	srand(time(NULL));
	int n = (rand() % 6) + 5;
	cout << "\n Number of vertices: " << n << "\n";

	int adjacencyMatrix[n][n];
	int i, j;

	// Fills the half of the initial matrix
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i >= j) adjacencyMatrix[i][j] = 0;
			else adjacencyMatrix[i][j] = (rand() % 10) + 1;
		}
	}

	// Fills the other half with the same values.
	for (i = 0; i < n; i++) for (j = 0; j < n; j++) if (i < j) adjacencyMatrix[j][i] = adjacencyMatrix[i][j];

	cout << "\n Adjacency Matrix: \n\n";
	// Prints initial values
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << setw(2) << adjacencyMatrix[i][j] << "  ";
		cout << "\n";
	}

	// To pass a variable sized 2d array to a functions as parameter
	int * matrix[n];
	for (i = 0; i < n; ++i) matrix[i] = adjacencyMatrix[i];

	// User is prompted to choose an MST algorithm
	int algo = promptUser();

	if (algo == 1) prim(matrix, n);
	else if (algo == 2) kruskal(matrix, n);
}

// param 1: adjacency matrix
// param 2: size of a single dimension
// Perform Prim`s MST algorithm
void prim(int ** matrix, int size)
{
	int i, edge_weight, queueSize;
	vertex priorityQueue[size];

	// Creates vertices and fills priorityQueus
	for (i = 0; i < size; i++)
	{
		vertex v;
		v.parentId = -1;
		v.id = i;
		v.cost = INT_MAX;
		priorityQueue[i] = v;
	}

	queueSize = size;
	priorityQueue[size - 1].cost = 0;

	// Loops until the priorityQueus is empty
	while (queueSize > 0)
	{
		// Takes the minimum element and removes it
		vertex v = priorityQueue[queueSize - 1];
		queueSize--;

		// Traverse all of its edges
		for (i = 0; i < size; i++)
		{
			// Do not traverse itself
			if (i != v.id)
			{
				edge_weight = matrix[i][v.id];

				// If we have this vertex and its weight is bigger than the last calculated weight
				// Then set the new weight to it, change its parent and keep the priority structure
				// by sorting again
				if (_include(priorityQueue, i, queueSize) &&
					getCost(priorityQueue, i, queueSize) > edge_weight)
				{
					setCost(priorityQueue, i, edge_weight, queueSize);
					setParentId(priorityQueue, i, v.id, queueSize);
					sort(priorityQueue, queueSize);
				}
			}
		}
	}

	cout << "\n All the edges in the MST by Prim:\n\n";
	for (i = 0; i < size - 1; i++)
	{
		cout << " V(";
		cout << priorityQueue[i].id + 1 << ") --- V(";
		cout << priorityQueue[i].parentId + 1 << ")  cost: ";
		cout << priorityQueue[i].cost << "\n";
	}
	cout << "\n";
}

// param 1: adjacency matrix
// param 2: size of a single dimension
// Perform Kruskal`s MST algorithm
void kruskal(int ** matrix, int size)
{
	int i, j, u, v;
	int mst_counter = 0;
	int edge_counter = 0;
	int totalEdges = size * (size - 1) / 2;

	vertex set[size];
	edge edges[totalEdges];
	edge edges_for_MST[size - 1];

	// Fills the set array which holds all vertices
	for (i = 0; i < size; i++)
	{
		vertex v;
		v.id = i;
		v.cost = 0;
		v.parentId = i;
		set[i] = v;
	}

	// Fills the edges array which holds all edges
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (j > i)
			{
				edge e;
				e.vertex_id_1 = i;
				e.vertex_id_2 = j;
				e.weight = matrix[i][j];

				edges[edge_counter] = e;
				edge_counter++;
			}
		}
	}

	// Edges sorted with increasing weight
	sortEdges(edges, totalEdges);

	// Loops until all the edges are traversed
	for (i = 0; i < totalEdges; i++)
	{
		// Get the shortest edge
		edge shortest_edge = edges[i];

		// Find the roots of both sides of the edge
		u = find3(set, shortest_edge.vertex_id_1);
		v = find3(set, shortest_edge.vertex_id_2); 

		// If roots are not same add it to the result and 
		// merge 2 different disjoint sets
		if (u != v)
		{
			edges_for_MST[mst_counter] = shortest_edge;
			mst_counter++;
			union3(set, u, v);
		} 
	}

	cout << "\n All the edges in the MST by Kruskal:\n\n";
	for (i = 0; i < size - 1; i++)
	{
		cout << " V(";
		cout << edges_for_MST[i].vertex_id_1 + 1 << ") --- V(";
		cout << edges_for_MST[i].vertex_id_2 + 1 << ")  cost: ";
		cout << edges_for_MST[i].weight << "\n";
	}
	cout << "\n";
}

// Given an array which holds edges, sorts them 
// according to increasing weight
void sortEdges(edge edges[], int size)
{
	int i, j;

	// Insertion sort
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (edges[i].weight < edges[j].weight)
			{
				edge e = edges[i];
				edges[i] = edges[j];
				edges[j] = e;
			}
		}
	}
}

// Given a set and index, finds the root and compress up to the root
int find3(vertex set[], int i)
{
	int root = set[i].parentId;
	int target = i, pId;

	// Find root of the forest
	while (root != set[i].id)
	{
		root = set[root].parentId; 
		i--;
	}

	// Compress path from i to root
	while (target != root)
	{
		pId = set[target].parentId;
		set[target].parentId = root;
		target = pId;
	}

	return root;
}

// Merges 2 disjoint sets by using height property of vertices
void union3(vertex set[], int i, int j)
{
	int root_id_x = find3(set, i);
	int root_id_y = find3(set, j);

	// Compare the levels set the lesser one`s parent to the bigger one
	// If both equal arbitrarily set one to other`s parent and increase the level 
	if (set[root_id_x].cost < set[root_id_y].cost) set[root_id_x].parentId = root_id_y;
	else if (set[root_id_x].cost > set[root_id_y].cost) set[root_id_y].parentId = root_id_x;
	else
	{
		set[root_id_y].parentId = root_id_x;
		set[root_id_x].cost++;
	}
}

// Getter function for cost field of vertex structure
int getCost(vertex queue[], int vertexId, int size)
{
	for (int i = 0; i < size; i++) if (queue[i].id == vertexId) return queue[i].cost;

	return -1;
}

// Setter function for cost field of vertex structure
void setCost(vertex queue[], int vertexId, int weight, int size)
{
	for (int i = 0; i < size; i++) if (queue[i].id == vertexId) queue[i].cost = weight;
}

// Setter function for parentId field of vertex structure
void setParentId(vertex queue[], int vertexId, int idToSet, int size)
{
	for (int i = 0; i < size; i++) if (queue[i].id == vertexId) queue[i].parentId = idToSet;
}

// Given a priority queue returns true if target vertex is found
bool _include(vertex priorityQueue[], int vertexToFind, int sizeOfQueue)
{
	for (int i = 0; i < sizeOfQueue; i++) if (priorityQueue[i].id == vertexToFind) return true;

	return false;
}

// Keep the priority queue structure by sorting vertexes according
// to decreasing cost values
void sort(vertex priorityQueue[], int size)
{
	int i, j;

	// Insertion sort
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (priorityQueue[i].cost > priorityQueue[j].cost)
			{
				vertex v = priorityQueue[i];
				priorityQueue[i] = priorityQueue[j];
				priorityQueue[j] = v;
			}
		}
	}
}

// return: 1 for Prim, 2 for Kruskal
// Prompts user to take input
int promptUser()
{
	int answer;
	cout << "\n Enter 1 for Prim, 2 for Kruskal: ";
	cin >> answer;

	if (answer != 1 && answer != 2) cout << " Selected algorithm is not found.\n\n";
	return answer;
}