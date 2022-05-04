#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <stack>
#include <list>
using namespace std;

#define MAX_NODES 140

// Global data structures to store city data

int adj[140][140];

map<const string, int> city;

vector<string> testCity;

vector<string> connectedFlight;

// Cole Schlotz Code here

/* bool BFS(int from, int to)
 *  By Cole Stoltz
 *  
 *  Parameters: int, int, int[]
 *
 *  Takes in 2 nodes. Calculates the least amount of connections
 *  from city A to B. Stores path inside of a path array.
 *
 *  Uses a breadth first search
 *   
 *  Returns: the minimum path a to the destination.
 */

bool BFS(int A, int B, int path[MAX_NODES])
{
	// Lists

	bool visited[MAX_NODES];

	list<int> queue;

	for (int i = 0; i < MAX_NODES; i++)
	{
		path[i] = -1;

	}

	// Current node

	int current_node = 0;

	// Set all visited to false

	for (int i = 0; i < MAX_NODES; i++)
	{
		visited[i] = false;

	}

	// insert starting node into queue

	queue.push_back(A);

	// While queue not empty IE still nodes to visit

	while (!queue.empty())
	{
		// Set current from front of queue

		current_node = queue.front();

		// Remove front node

		queue.pop_front();

		// Add nodes that need to be visited

		for (int i = 0; i < 140; i++)
		{
			// If the has not been visited and there is connection

			// Set that node to visited (its not visited yet)

			// Then add it to queue visit and pop	// Prevents cycles

			if (!visited[i] && adj[current_node][i] == 1)
			{
				visited[i] = true;

				queue.push_back(i);

				path[i] = current_node;

				if (i == B)
				{
					return true;

				}
			}
		}
	}

	return false;

}

/* void AtoA(int city)
 *
 *  By Cole Stoltz
 *  
 *  Parameters: int
 * 
 *  Takes in 1 node. Calculates the least amount of connections
 *  from city A back to city A.
 *
 *  Uses a breadth first search from BFS function
 *   
 *  Returns: the minimum path a to the destination.
 */

void AtoA(int A)
{
	// Temp variables

	int tempB = A;

	// For path tracing the nodes

	int path[MAX_NODES];

	stack<int> stack_path;

	// Call bfs function to check if route possible

	if (BFS(A, tempB, path))
	{
		cout << "\n\nRoute possible -------" << endl;

		// Add path to stack

		while (path[tempB] != A)

		{
			tempB = path[tempB];

			stack_path.push(tempB);

		}

		// Print initial city

		cout << testCity[A];

		// Print path that was pushed to stack

		while (!stack_path.empty())

		{
			cout << " -> " << testCity[stack_path.top()];

			stack_path.pop();

		}

		cout << " -> " << testCity[A] << endl << endl;

	}
	else
	{
		cout << "No route back to city -> " << testCity[A] << endl;

	}
}

// END

// Vladimer Purtskhvanidze

void addEdge(int node1, int node2)
{
	adj[node1][node2] = 1;
};

void DFS(int start, int end, int totalConnection, vector<int> route, vector<int> &shortRoute, bool visited[])

{
	if (start == end)	// if path found

	{
		if (shortRoute.size() == 0 || shortRoute.size() > route.size())

		{
			shortRoute.assign(route.begin(), route.end());	//assign path to vector
		}

		return;
	}

	if (route.size() == totalConnection + 1)	// in case user wants specify connection number and if not posssible exit code

	{
		return;
	}

	for (int k = 0; k < 140; k++)	//for each city

	{
		if (k != start && adj[start][k] == 1 && visited[k] == false)	//if adjacent and not visited before

		{
			visited[k] = true;	// visited k

			route.push_back(k);	// add to route

			DFS(k, end, totalConnection, route, shortRoute, visited);	//call function 

			visited[k] = false;

			route.pop_back();
		}
	}
}

bool contains(vector<int> route, int k, int l)	//function to check if route cointains city B and C

{
	return (find(route.begin(), route.end(), k) != route.end()) && (find(route.begin(), route.end(), l) != route.end());
}

bool possible = true;

void canfly(string Start, string End, int connectionNumber)

{
	int A = city[Start];	// get Number for city

	int B = city[End];	// get Number for city

	if (A == 140 || B == 140)

	{
		cout << "Atleast one of the city names is wrong!!" << endl;

		return;
	}

	bool visitedCity[140];

	vector<int> totalRoute;

	vector<int> shortRoute;

	for (int i = 0; i < 140; i++)

	{
		visitedCity[i] = false;	// set all city to not visited 
	}

	visitedCity[A] = true;	//set start city to visited

	totalRoute.push_back(A);	// add start city to route

	DFS(A, B, connectionNumber, totalRoute, shortRoute, visitedCity);

	totalRoute.pop_back();
	vector<string> flightAtoB;

	visitedCity[A] = false;

	int shortPath = shortRoute.size();	// get size of route 

	if (shortPath != 0)	// if route found 

	{
		cout << "Yes! It is Possible: " << endl;

		for (int i = 0; i < shortPath - 1; i++)	// for each Integer in Route 

		{
			cout << testCity[shortRoute[i]] << " -> ";	// display path
			connectedFlight.push_back(testCity[shortRoute[i]]);	//using this for A to D through B and C
			flightAtoB.push_back(testCity[shortRoute[i]]);
		}

		cout << testCity[shortRoute[shortPath - 1]] << endl;

		cout << "Total Number Of Connections: " << flightAtoB.size() << endl;
		cout << "###################################" << endl;
	}
	else

	{
		cout << "No! Route Not Found." << endl;
		possible = false;
	}
}

int main()
{
	string number;
	string filename;
	vector<string> cityToNumbers;

	fstream cityFile;
	fstream filghtFile;
	regex self_regex("From");

	int node1, node2;
	cityFile.open("city.name", ios:: in);
	if (cityFile.is_open())	// if file open
	{
		int amountOfFloats = 0;
		int fromCity = 0;
		int toCity = 0;

		while (getline(cityFile, number))	// for each float number
		{
			city[number] = amountOfFloats;
			if (regex_search(number, self_regex))
			{
				cout << number << endl;
				cityToNumbers.push_back(to_string(amountOfFloats));	// from city
			}

			cout << "total City " << city[number] << " " + number << endl;
			testCity.push_back(number);

			amountOfFloats++;
		}

		cityFile.close();

		filghtFile.open("flight.txt", ios:: in);
		string flight;
		while (getline(filghtFile, flight))	// for each float number
		{
			if (regex_search(flight, self_regex))
			{
				// from city
				// from city
				flight.erase(0, 7);
				node1 = city[flight];
			}
			else
			{
				flight.erase(0, 7);
				node2 = city[flight];
				addEdge(node1, node2);
			}
		}

		for (int x = 0; x < 140; x++)
		{
			cout << x << " --> ";
			for (int z = 0; z < 140; z++)
			{
				if (adj[x][z])
				{
					cout << z << " ";
				}
			}

			cout << endl;
		}

		int option;
		string startCity, cityA, cityB, cityC, EndCity;

		cout << "Select option 1 to calculate routes from A to B" << endl;
		cout << "Select option 2 to calculate routes from A to B through C and D " << endl;
		cout << "Select option 3 to calculate rroutes to travel From A, B ,C to 1 specific city" << endl;
		cout << "Select option 4 to travel All cities and come back" << endl;
		cout << " Select 5 to exit " << endl;
		cin >> option;

		if (option == 1)
		{
			cout << "Enter Start" << endl;
			cin.ignore();
			getline(cin, startCity);
			int startCityToInt = city[startCity];

			cout << startCityToInt << endl;
			cout << "Enter End" << endl;
			getline(cin, EndCity);
			int endCityToInt = city[EndCity];
			int x = 10;
			canfly(startCity, EndCity, x);
			// fromAtoB(startCityToInt, endCityToInt);
		}

		if (option == 2)
		{
			cout << "Enter Start" << endl;
			cin.ignore();
			getline(cin, startCity);
			int startCityToInt = city[startCity];

			cout << startCityToInt << endl;
			cout << "Enter End" << endl;
			getline(cin, EndCity);

			cout << "city B" << endl;
			getline(cin, cityB);
			cout << "city C" << endl;
			getline(cin, cityC);
			int endCityToInt = city[cityB];
			int x = 10;
			// canfly(startCity, EndCity, x);
			canfly(startCity, cityB, x);
			canfly(cityB, cityC, x);
			canfly(cityC, EndCity, x);
			if (possible == true)
			{
				for (int i = 0; i < connectedFlight.size(); i++)
				{
					cout << connectedFlight.at(i) + "->  ";
				}

				cout << EndCity << endl;
				cout << "Total connection: " << connectedFlight.size() << endl;
			}
		}

		if (option == 3)
		{
			cout << "Enter Start city for 1st traveler" << endl;
			cin.ignore();
			getline(cin, cityA);

			cout << "Enter Start city for 2nd traveler" << endl;
			getline(cin, cityB);

			cout << "Enter Start city for 3rd traveler" << endl;
			getline(cin, cityC);
			cout << "Enter Destination" << endl;
			getline(cin, EndCity);
			int endCityToInt = city[cityB];
			int x = 10;

			canfly(cityA, EndCity, x);
			canfly(cityB, EndCity, x);
			canfly(cityC, EndCity, x);

		}

		if (option == 4)
		{
			// Ignore last input to prevent overflow
			cin.ignore();

			// Get user input for the city to loop back to
			cout << "Enter starting city: ";	// -------- Start city
			getline(cin, startCity);
			cout << endl;

			// Call function
			AtoA(city[startCity]);

		}

		if (option == 5)
		{
			cout << "Exiting..." << endl;
			return 0;
		}

		filghtFile.close();
	}
	else
		cout << "Unable to open file";

	return 0;
}
