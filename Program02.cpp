//Krishna Sai Chemudupati
#include <iostream>
#include <vector>
using namespace std;

void printAdjMatrix(int** graph, int vertices)
{
	for (int i = 0; i < vertices; i++)
	{
		cout << "|";
		for (int j = 0; j < vertices; j++)
		{
			cout << graph[i][j] << " ,";
		}
		cout << "|" << endl;
	}
}

//prints the Path
void printPath(vector<int> path)
{
	if (path.size() > 1)
	{
		for (int i = 0; i < path.size();i++)
		{
			if (i == path.size() - 1)
			{
				cout << path[i] << endl;
			}
			else
			{
				cout << path[i] << "-> ";
			}
		}
	}
	else if (path.size() == 1)
	{
		cout << "You are already at the node: "<< path[0] << endl;
	}
	else
	{
		cout << "A path wasn't found. Please check values of source and sink." << endl;
	}
	
}

//returns the index to univisited neighbour for a given node. The way the function is implemented, it returns the neighbour with the least index. 
int indexToUnVisitedNode(int** redsidualGraph, const int* visitStatus, const int currentNode, const int vertices)
{
	int output = -1;
	bool found = false;
	//stop search if you checked all neighbours |OR| you found the neighbour.
	for (int i = 0; i < vertices && found == false; i++)
	{
		if (redsidualGraph[currentNode][i] != 0)
		{
			if (visitStatus[i]==0)
			{
				output = i;
				found = true;
			}
		}
	}
	return output;
}
//Gives an augmented path from source to sink. Returns an empty vector if path wasnt found. If source equals sink it return a vector containing the source/sink.
//I chose residual graph to be an adjacency matrix because its easier to visualize from the which node to which node the endge exists and the weight of the edge is easily found with O(1).
// I am assumsing non-negative edge weights.
vector<int> getAugmentedPath(int ** residualGraph, const int vertices, const int source, const int sink)
{
	//making an array to hold if the nodes are visited or not. 0 for not visited and 1 for visited. 
	//used an array as it takes only O(1) to find if the node is visited or not. 
	int* visitStatus = new int[vertices];
	//setting all nodes to unvisited.
	for (int i = 0; i < vertices; i++)
	{
		visitStatus[i] = 0;
	}
	//vector keeps track of the nodes visited, and acts like a stack. It will also be the output in the end.
	//Used a vector in this case beacause you dont need to worry about the top index, its easy to push and pop of the vector implemented stack.
	vector<int> visited;
	//i want the program to stop if the sink node was found. 
	bool found = false;
	if (source == sink)
	{
		found = true;
	}
	//DFS
	//checking if the source and if the source and sink are reasonable values.
	if (source>-1 && source<vertices && sink < vertices && sink >-1) 
	{
		//changing the visitStatus of source to visited.
		visitStatus[source] = 1;
		//pushing source into visited stack. 
		visited.push_back(source);
		//position is what makes the vector a stack. Position denotes the top of the stack. 
		int position = 0;
		//the while loop stops if it has visited all the nodes.|OR| it stops if sink was found |OR| it has come back to the source and its neighbours are all visited. 
		while (visited.size() < vertices && !found && position >-1)
		{
			//index set to immeadiate neighbour. 
			int index = indexToUnVisitedNode(residualGraph, visitStatus, visited[position], vertices);
			//stops the loop if all neighbours are visited, or the sink was found. 
			while (index > -1 && !found)
			{
				//changing visit status of the node to visited.
				visitStatus[index] = 1;
				//pushing the node to the 'visited' stack.
				visited.push_back(index);
				//changing the top of the stack.
				position++;
				//if sink is found change the 'found' to true.
				if (index == sink)
				{
					found = true;
				}
				//find the next node in the potenial path.
				index = indexToUnVisitedNode(residualGraph, visitStatus, visited[position], vertices);
			}
			//only if the sink is not found, 
			if (!found)
			{
				//changing the top of the stack.
				position--;
				//popping the previous top node off the stack.
				visited.pop_back();
			}		
		}
	}	
	return visited;
}



int main()
{
	int size = 8;
	int** adjMatrix = new int*[size];
	for (int i = 0; i < size; i++)
	{
		adjMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}
	adjMatrix[0][1] = 2;
	adjMatrix[0][2] = 1;
	adjMatrix[0][3] = 4;
	adjMatrix[1][2] = 1;
	adjMatrix[1][4] = 10;
	adjMatrix[1][5] = 2;
	adjMatrix[2][0] = 9;
	adjMatrix[2][4] = 8;
	adjMatrix[3][2] = 2;
	adjMatrix[4][3] = 7;
	adjMatrix[4][6] = 1;
	adjMatrix[5][7] = 3;
	adjMatrix[6][4] = 4;
	adjMatrix[6][5] = 2;
	adjMatrix[7][6] = 1;

	printAdjMatrix(adjMatrix, size);
	cout << endl;
	printPath(getAugmentedPath(adjMatrix, size, 7, 7));
    return 0;
}

