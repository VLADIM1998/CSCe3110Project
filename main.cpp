#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <regex>

using namespace std;

//Cole Schlotz Code here 
 






//END 
int adj[140][140];

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

      /// adj[][] we have this matrix ready I am still working on first function 
      //adj['Casablanca, Morocco']['Brussels, Belgium] will display if they adjacent 1 means there is direct flight 0 means nmo flight
      // choose any 2 function
      // Let me know if any question 
      
    }
    if(option == 3){
      
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