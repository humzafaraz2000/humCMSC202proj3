//Title: Route.cpp
//Author: Humza Faraz
//Date: 3/28/19
//Section: 32
//E-mail: hfaraz1@umbc.edu
//Description: Creates route full of stops

#include <string>
#include "Route.h"
#include "BusCompany.h"
#include <iostream>
#include <cmath>

// Name: Route() - Default Constructor
// Desc: Used to build a new bus route (which is a linked list)
// Preconditions: None
// Postconditions: Creates a new bus route where m_start and m_end point to NULL
Route::Route(){
  m_start = NULL;
  m_size = 0;
}

// Name: ~Route() - Destructor
// Desc: Used to destruct a route (which is a linked list)
// Preconditions: There is an existing route with at least one stop
// Postconditions: A route is deallocated (including all dynamically allocated stops)
//                 to have no memory leaks!
Route::~Route(){
  Clear();
}

// Name: InsertAt
// Preconditions: Takes in a name, location, number of riders,
//                and a cost (in dollars).
//                Creates new stop.
//                Inserts each Stop based on their integer location.
//                Requires a route.
// Postconditions: Adds a new stop to the route at a unique location.
void Route::InsertAt(string name, int location, int riders, double cost){
  Stop *newStop = new Stop(name, location, riders, cost);
  //adds to beginning
  if (m_size == 0){
    m_start = newStop;
    m_size++;
  }
  //adds to beginning if beginning is already full
  else if (location < m_start->m_location){
    newStop->m_next = m_start;
    m_start = newStop;
    m_size++;
  }
  else{
    Stop* temp = m_start;
    Stop* prev;
    //adds to end
    while (temp->m_location < location){
      if (temp->m_next == NULL){
        temp->m_next = newStop;
        m_size++;
        return;
      }
      prev = temp;
      temp = temp->m_next;
    }
    //adds to middle
    newStop->m_next = temp;
    prev->m_next = newStop;
    m_size++;
  }
  
 
}

// Name: DisplayRoute
// Preconditions: Outputs the route.
// Postconditions: Returns a numbered list of all stops on a route.
void Route::DisplayRoute(){
  Stop* current = m_start;
  int count = 0;
  //Displays all stops except last
  while (current->m_next != NULL){
    cout << "Stop " << count+1 << " - " << current->m_name << "(" << current->m_location << ")" << endl;
    current = current->m_next;
    count ++;
  }
  //Displays last stop
  if (current != NULL){
    cout << "Stop " << count+1 << " - " << current->m_name << "(" << current->m_location << ")" << endl;
  }
  cout << "END"<<endl;
}

// Name: IsEmpty
// Preconditions: Requires a route
// Postconditions: Returns if the route is empty.
bool Route::IsEmpty(){
  if (m_start->m_next == NULL){
    return true;
  }
  else{
    return false;
  }
}

// Name: GetRouteEarnings
// Preconditions: Requires a bus route
// Postconditions: Iterates over complete route and sums total earnings per month
//                 Fare per rider * riders per stop (Fare is a constant in BusCompany.h)
double Route::GetRouteEarnings(double riderFare){
  double totalEarnings = 0;
  //adds up earnings by iterating through each element of list
  Stop* temp = m_start;
  while(m_start->m_next != NULL){
    double earning = 0;
    earning = temp->m_riders * riderFare;
    totalEarnings += earning;
    temp = temp->m_next;
  }
  return totalEarnings;
}

// Name: GetRouteExpenses
// Preconditions: Requires a Bus Route
// Postconditions: Iterates over route and sums total cost per station per month
double Route::GetRouteExpenses(){
  Stop* temp = m_start;
  double totalExpenses = 0;
  while(m_start->m_next != NULL){
    totalExpenses += temp->m_cost;
    temp = temp->m_next;
  }
  return totalExpenses;
}

// Name: Clear
// Preconditions: Requires a route
// Postconditions: Removes all stops in a route
void Route::Clear(){
  Stop* check = m_start;
  Stop* temp;
  while(check != NULL) {
		temp = check->m_next;
		delete check;
		check = temp;
	}
  
}

// Name: OptimizeRoute
// Desc: Iterates over a bus route. If a specfic stop earns less than it's cost, it is removed
//       from the route by calling RemoveStop.
//       Earning = fare * number of riders and cost = m_cost
// Preconditions: Requires a Bus Route
// Postconditions:  Removes stops where (fare * riders) < monthly cost for station
void Route::OptimizeRoute(double riderFare){
  Stop* check = m_start;
  while (check->m_next != NULL){
    double profit = check->m_riders * riderFare;
    if (profit < check->m_cost){
      int location = check->m_location;
      RemoveStop(location);
    }
    check = check->m_next;
  }
}

// Name: RemoveStop
// Preconditions: Requires a Bus Route
// Postconditions: Removes a specific bus stop
void Route::RemoveStop(int stopLocation){
  
  Stop* check = m_start;
  int location = check->m_location;
  Stop *ptr;
  
  while (location != stopLocation){
    ptr = check;
    check = check->m_next;
    location = check->m_location;
  }
    
  if (check == m_start){
      
    m_start = check->m_next;
    delete check;  
  }
  else{
      
      ptr->m_next = check->m_next;
      delete check;
      cout << "Element deleted" << endl;
    }
  m_size--;
}

// Name: GetStopData
// Desc: Displays name, earnings and expenses for stop
// Preconditions: Requires a bus route passed riderFare (from constant in BusCompany.h)
// Postconditions: None
void Route::DisplayStopData(double riderFare){
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  Stop* check = m_start;
  while(check->m_next != NULL){
    double profit = check->m_riders * riderFare;
    double total = profit - check->m_cost;
    cout << check->m_name << endl;
    cout << " Earnings: " << check->m_riders << "@$" << riderFare << " = " << "$" << profit << endl;
    cout << " Expenses: $" << check->m_cost << endl;
    cout << " Total: $" << total << endl;
    check = check->m_next;
  }
}

// Name: GetSize
// Precondition: Requires a bus route
// Postcondition: Returns the number of stops in the route as an integer
int Route::GetSize(){
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Preconditions: Requires a route with stops
// Postconditions: Returns a route with stops separated by ->
std::ostream &operator<< (ostream &output, Route &myRoute){
  Stop* check = myRoute.m_start;
  while (check->m_next != NULL){
    output << check << "->";
    check = check -> m_next;
  }
  return output;
}
