#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <list>

using namespace std;
#define MAX_NODES 140

//Cole Schlotz Code here 
// Used in loops and maximum nodes

// Adjaceny list // Global
int adj[140][140];

//Cole Stoltz Code here 
/*  void BFS(int from, int to)
 *
 *   By Cole Stoltz
 *  
 *   Parameters: int, int, int[]
 *
 *   Takes in 2 nodes. Calculates the least amount of connections
 *   from city A to B.
 *
 *   Uses a breadth first search
 *   
 *   Returns: the minimum path a to the destination.
 */
bool BFS(int A, int B, int path[MAX_NODES]) {

  // Lists
  bool visited[MAX_NODES];
  list < int > queue;

  for (int i = 0; i < 140; i++) {
    path[i] = -1;
  }

  // Iterator for moving through list
  list < int > ::iterator it;

  // Current node
  int current_node = 0;

  // Set all visited to false
  for (int i = 0; i < MAX_NODES; i++) {
    visited[i] = false;
  }

  // Set start node to visited
  visited[A] = true;

  // insert starting node into queue
  queue.push_back(A);

  // While queue not empty IE still nodes to visit
  while (!queue.empty()) {
    // Set current from front of queue
    current_node = queue.front();
    cout << current_node << "--" << endl;
    // Remove front node
    queue.pop_front();

    // Add nodes that need to be visited
    for (int i = 0; i < 140; i++) {
      // If the has not been visited and there is connection
      // Set that node to visited (its not visited yet)
      // Then add it to queue visit and pop // Prevents cycles
      if (!visited[i] && adj[current_node][i] == 1) {
        visited[i] = true;
        queue.push_back(i);
        path[i] = current_node;

        if (i == B) {
          return true;
        }

      }

    }
  }
  return false;
}

/*  void BFS(int from, int to)
 *
 *   By Cole Stoltz
 *  
 *   Parameters: int, int, int, int
 *
 *   Takes in 4 nodes. Calculates the least amount of connections
 *   from city A to D traveling through city B and C. 
 *
 *   Analyzes the path provided by the BFS function
 *   
 *   Returns: Prints the path of the connection if there is one.
 */
void AtoBtoCtoD(int A, int B, int C, int D){
  
  // Path edited by the BFS function
  int path[MAX_NODES];
  stack< int > stack_path;

  // Checks for A -> B or if A -> C returned true
  bool AtoB = false;
  bool AtoC = false;
  bool BtoC = false;
  bool CtoB = false;
  bool CtoD = false;
  bool BtoD = false;

  // Temp variables as A and B would be modified
  int tempB = B;
  int tempC = C;
  int tempD = D;

  // Go through each node A->B->C->D or A->C->B->D
  // Therefore many if statements used
  // Could have been made more streamlined
  // Checks for valid A -> B or A -> C
  if(BFS(A, B, path)){ 
    AtoB = true;
    while(path[tempB] != -1){
      stack_path.push(tempB);
      tempB = path[tempB];
    }
    tempB = B;
  } else if(BFS(A, C, path) && AtoB == false){
    AtoC = true;
    while(path[tempC] != -1){
      stack_path.push(tempC);
      tempC = path[tempC];
    }
    tempC = C;
  } else{
      cout << " | No connection to final city can be made..." << endl;
    return;
  }

  // Print if valid
  cout << A;
  while(!stack_path.empty()){
    cout  << " -> " << stack_path.top();
    stack_path.pop();
  } 

  // Checks for valid A -> B or A -> C
  if(BFS(B, C, path)){ // Check a to b or a to c
    while(path[tempC] != -1){
      stack_path.push(tempC);
      tempC = path[tempC];
    }
    tempC = C;
  } else if(BFS(C, B, path) && AtoC == true){
    CtoB = true;
    while(path[tempB] != -1){
      stack_path.push(tempB);
      tempB = path[tempB];
    }
    tempB = B;
  } else{
      cout << " | No connection to final city can be made..." << endl;
    return;
  }
  
  // Print if valid
  while(!stack_path.empty()){
    cout  << " -> " << stack_path.top();
    stack_path.pop();
  } 

  // Checks for valid A -> B or A -> C
  if(BFS(C, D, path)){ // Check a to b or a to c
    while(path[tempD] != -1){
      stack_path.push(tempD);
      tempD = path[tempD];
    }
    tempD = D;
  } else if(BFS(B, D, path) && CtoB == true){
    while(path[tempD] != -1){
      stack_path.push(tempD);
      tempD = path[tempD];
    }
    tempD = D;
  } else{
      cout << " | No connection can be made..." << endl;
    return;
  }

  // Print if valid
  while(!stack_path.empty()){
    cout  << " -> " << stack_path.top();
    stack_path.pop();
  } 
  cout << endl;

}

//END 

// Vladimer Purtskhvanidze 

 void addEdge  (int node1, int node2){
    adj[node1][node2] = 1; 
    };


 void fromAtoB (int from,int to){
   cout<<from<<endl;
   cout<<to<<endl;
     cout<<"adjacent?"<<endl;
     vector <int>  visitedCities ;
     vector <int>  transferCities;
     int connection = 0;

   cout<<adj[from][to]<<endl;;//[2] [85]   if 1 there is direct flight
  bool found = false;
  for(int s=0;s<140;s++){
    if(adj[from][s] ==1){
      cout<<s<<endl;
      transferCities.push_back(s);
      if(s == to){
        cout<<"we have direct Flight total Connection 1"<<endl;
        found = true;
        return;
      } 

    }
  }
  if(found == false){
    connection++;
  }

   for(int z=0;z<transferCities.size();z++){

     for(int a=0;a<140;a++){
       if(adj[transferCities.at(0)][a] == 1){
         transferCities.push_back(a); //

           if(a == to){
          
            found=true;
            return;
       }
       }
     
       
     }
     
        transferCities.erase(transferCities.begin());
         connection ++;
   }
  


 }//fromAtoB

int main () {
  string number;
  string filename;
  vector <string>  cityToNumbers ;
  map< const string, int> city;
  fstream cityFile;
  fstream filghtFile;
  regex self_regex("From");
 
   // City variables --- Maps to an int or "node"
  string startCity;
  string endCity;
  string cityB;
  string cityC;
  
  int node1,node2;
  cityFile.open("city.name",ios::in);
  if (cityFile.is_open())//if file open 
  {
      
      int amountOfFloats=0;
      int fromCity=0;
      int toCity=0;
      
    while ( getline(cityFile,number) ) // for each float number 
    {
    
      city[number] = amountOfFloats;
      if(regex_search(number,self_regex)){
         cout<<number<<endl;
         cityToNumbers.push_back(to_string(amountOfFloats)); // from city 

      }
      cout << "total City " <<city[number]<< " " + number <<endl;


      amountOfFloats ++;

    }
     cityFile.close();

    filghtFile.open("flight.txt",ios::in);
     string flight;
     while ( getline(filghtFile,flight) ) // for each float number 
    {
    
    
      if(regex_search(flight,self_regex)){ //from city 
          //from city 
          flight.erase(0,7);
          node1 = city[flight];

      }
      else{
        flight.erase(0,7);
        node2 = city[flight];
        addEdge(node1,node2);
      }
     
      


     

    }

    for(int x=0;x<140;x++){
      cout<< x << " --> ";
        for(int z=0;z<140;z++){
           if(adj[x][z]){
             cout << z <<" ";
           }
        }
         cout << endl;
       
    }

   int option;
   string startCity,EndCity;
  cout<<"Select option 1 to calculate routes from A to B"<<endl;
  cout<<"Select option 2 to calculate routes from A to B through C and D "<<endl;
   cout<<"Select option 3 to calculate routes to travel all cities from A and come back"<<endl;
    cout<<"Select option 4 to calculate routes to travel From A , B ,C to 1 specific city"<<endl;
    cout<<" Select 5 to exit "<<endl;
    cin>>option;
    

    if(option == 1){
      cout<<"Enter Start"<<endl;
      cin.ignore();
      getline(cin,startCity);
      int startCityToInt = city[startCity];
      cout<<startCityToInt<<endl;
      cout<<"Enter End"<<endl;
      getline(cin,EndCity);
      int endCityToInt = city[EndCity];

       fromAtoB(startCityToInt,endCityToInt);

    }
    if(option == 2){

      
      // Ignore last input to prevent overflow
      cin.ignore();

      // Get user input for the 4 cities
      cout << "Enter starting city: "; // -------- Start city
      getline(cin, startCity);
      cout << endl;

      cout << "Enter ending city: "; // ---------- End city
      getline(cin, endCity);
      cout << endl;

      cout << "Enter intermediate city 1: "; // -- City B
      getline(cin, cityB);
      cout << endl;

      cout << "Enter intermediate city 2: "; // -- City C
      getline(cin, cityC);
      cout << endl;

      AtoBtoCtoD(city[startCity], city[cityB], city[cityC], city[endCity]);

      
    }
    if(option == 3){
      int path[MAX_NODES];
      
      
    }
    if(option == 4){
      
    }
    if(option == 5){
      return 0;
    }
    
    


   // cout<<"Moscow"<<endl;
    //cout<<city["Moscow, Russia"]<<endl;

    // cout << "total City " <<amountOfFloats<<endl;
   
    //cout << "average of float numbers = "<<average <<endl;  
    
    filghtFile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
