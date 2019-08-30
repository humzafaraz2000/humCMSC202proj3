//Title: BusCompany.cpp
//Author: Humza Faraz
//Date: 3/28/19
//Section: 32
//E-mail: hfaraz1@umbc.edu
//Description: Creates a vector full of routes(linked lists).

#include "BusCompany.h"
#include "Route.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Name: BusCompany (default constructor)
// Preconditions: None
// Postconditions: A new bus company is created.
BusCompany::BusCompany(){
  m_newRoute = NULL;
}

// Name: BusCompany (overloaded constructor)
// Desc: Calls ReadFile and then MainMenu
// Preconditions: Filename is included
// Postconditions: A new bus company is created and routes are created from a passed file
BusCompany::BusCompany(string fileName){
  m_newRoute = NULL;
  ReadFile(fileName);
  MainMenu();
  
}

// Name:  BusCompany (destructor)
// Preconditions: None
// Postconditions: All linked lists are destroyed.
BusCompany::~BusCompany(){
  for (int i= 0; i < (int) m_routes.size(); i++){
    m_routes[i]->Clear();
  }
}

// Name:  readFile
// Desc: Populates a vector of linked lists (m_routes of Routes)
// Preconditions: Valid file name of routes
// Postconditions: Creates one route as described (file may have multiple routes)
void BusCompany::ReadFile(string fileName){
  ifstream myfile;
  string name;
  int locat;
  int riders;
  double cost;
  myfile.open(fileName);
  int numStops = 0;
  if (m_newRoute == NULL){
    m_newRoute = new Route();
  }
  
  if(myfile.is_open()){
    //get name
    while(getline(myfile, name, ',')){
      if (name != "End Route"){
        myfile >> locat;
        myfile >> riders;
        myfile >> cost;
        if (myfile.peek() == '\n'){
          myfile.ignore();
        }      
  
      m_newRoute->InsertAt(name, locat, riders, cost);
      numStops++;        
      }

      if (name == "End Route"){
        m_routes.push_back(m_newRoute);
        m_newRoute = new Route();
      }
      
    }
    
    myfile.close();
  }else{
     cout << "Unable to to open file." << endl;
  }
  
} 


  
// Name:  mainMenu
// Preconditions: None
// Postconditions: None
void BusCompany::MainMenu(){
  
  int choice;
  cout << "********************************" << endl;
  cout << "Welcome to UMBC Transit Simulator" << endl;
  cout << "What would you like to do?:" << endl << "1. Display Routes" << endl << "2. Display Earnings" << 
    endl << "3. Optimize Route" << endl << "4. Exit" << endl;
  cin >> choice;

  while (choice != 4){
    if (choice == 1){
      DisplayRoutes();
        cout << "What would you like to do?:" << endl << "1. Display Routes" << endl << "2. Display Earnings" << 
          endl << "3. Optimize Route" << endl << "4. Exit" << endl;
        cin >> choice;
    }
    else if (choice == 2){
      DisplayRouteData();
      cout << "What would you like to do?:" << endl << "1. Display Routes" << endl << "2. Display Earnings vs. Expenses" << 
        endl << "3. Optimize Route" << endl << "4. Exit" << endl;
      cin >> choice;
    }
    else if (choice == 3){
      OptimizeRoute();
      cout << "What would you like to do?:" << endl << "1. Display Routes" << endl << "2. Display Earnings" << 
        endl << "3. Optimize Route" << endl << "4. Exit" << endl;
      cin >> choice;
    }
    else{
      cout << "Invalid. Enter 1-4." << endl; 
      cout << "What would you like to do?:" << endl << "1. Display Routes" << endl << "2. Display Earnings" << 
        endl << "3. Optimize Route" << endl << "4. Exit" << endl;      
      cin >> choice;
    }
  }
  cout << "Thank you for using UMBC transit simulator." << endl;

}
  
// Name:  DisplayRoutes
// Desc: Iterates over the vector and calls the overloaded << operator for each route
// Preconditions: At least one route in m_routes;
// Postconditions: Displays each route in m_routes
void BusCompany::DisplayRoutes(){
  for (int i = 0; i < (int)m_routes.size(); i++){
    cout << "*** Route " << i+1 << " ***" << endl;
    m_routes.at(i)->DisplayRoute();
  }
}
  
// Name:  OptimizeRoute
// Desc: Goes through a specific route and removes profit losing stops (3.25 per rider)
//       Profit is riders * fare per rider vs stop cost
// Preconditions: Has route
// Postconditions: Removes up to all stops in a route that lose money
void BusCompany::OptimizeRoute(){
  if (m_routes.size() > 1){
    int choice = 0;
    cout << "Which route would you like to optimize?" << endl;
    cin >> choice;
    while (choice < 0 or choice > (int)m_routes.size()){
      cout << "Invalid choice." << endl;
      cin >> choice;
    }
    m_routes.at(choice-1)->OptimizeRoute(RIDER_FARE);
  }
  else{
    m_routes.at(0)->OptimizeRoute(RIDER_FARE);
  }
} 

// Name:  DisplayRouteData()
// Desc: Displays total earnings and total expenses per route
//       Displays earnings/expenses by individual stop by route
// Preconditions: Has route
// Postconditions: Displays route with stop data
void BusCompany::DisplayRouteData(){
  int count = 0;
  while (count < (int)m_routes.size()){
    cout << "*** Route " << count+1 << " ***" << endl;
    m_routes.at(count)->DisplayStopData(RIDER_FARE);
    count++;
  }
}