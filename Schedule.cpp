#include "Schedule.h"

// Name: Schedule() - Default Constructor
// Desc: Used to build a new Schedule 
// Preconditions: None
// Postconditions: Creates a new Schedule where m_head and m_tail point to nullptr and size = 0
Schedule::Schedule(){
  m_head = nullptr;
  m_tail = nullptr;
  m_name = "Default";
  m_size = 0;
}
// Name: Schedule(string) - Overloaded Constructor
// Desc: Used to build a new Schedule with the schedule name passed
// Preconditions: None
// Postconditions: Creates a new Schedule where m_head and m_tail point to nullptr and schedule name is passed
Schedule::Schedule(string name){
  m_head = nullptr;
  m_tail = nullptr;
  m_name = name;
}// Name: ~Schedule() - Destructor
// Desc: Used to destruct a strand of Schedule
// Preconditions: There is an existing Schedule strand with at least one node
// Postconditions: Schedule is deallocated (including all dynamically allocated nodes)
//                 to have no memory leaks!
Schedule::~Schedule(){
  cout << "Deleting Schedules" << endl;
  Item* curr = m_head;
  while (curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }
  m_name = "";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}
// Name: InsertSorted
// Desc: Inserts a new item into the schedule. Inserts it from earliest time (0) to highest time (2359) ascending
//       Does NOT insert at correct location when reversed
// Preconditions: Takes in an Item pointer. Inserts the node based on time.
//                Requires a Schedule
// Postconditions: Adds the new item into the Schedule.
void Schedule::InsertSorted(Item* newItem){
  if(m_head == nullptr){ 
    m_head = newItem; 
    //m_tail = newItem;
  }  
  else if (newItem->GetTime() < m_head->GetTime()){
    newItem->SetNext(m_head);
    m_head = newItem;
  }
  else {
    Item* temp = m_head;
    Item* previous;
    while (temp->GetTime() < newItem->GetTime()){
      if (temp->GetNext() == nullptr){
        temp->SetNext(newItem);
        //m_tail->SetNext(newItem);
        m_size++;
        return;
      }
      else{
        previous = temp;
        temp = temp->GetNext();
      }
    }
    newItem->SetNext(temp);
    previous->SetNext(newItem);
  }
  m_size++;
}
// Name: GetName()
// Preconditions: Requires a Schedule
// Postconditions: Returns m_name;
string Schedule::GetName(){
    return m_name;
}
// Name: GetSize()
// Preconditions: Requires a Schedule
// Postconditions: Returns m_size;
int Schedule::GetSize(){
    return m_size;
}
// Name: ReverseSchedule
// Preconditions: Reverses the Schedule
// Postconditions: Schedule is reversed in place; nothing returned
void Schedule::ReverseSchedule(){
  Item* current = m_head;
  Item* prev = NULL;
  Item* next;
  while (current != NULL){
    next = current->GetNext();
    current->SetNext(prev);
    prev = current;
    current = next;
  }
  m_head = prev;
}
// Name: GetData
// Desc: Returns the time at a specific location in the Schedule
//       Pass 
// Preconditions: Requires a Schedule
// Postconditions: Returns data from specific item
 // Note: May not be used in project but still required
Item* Schedule::GetData(int nodeNum){
  Item* temp = m_head;
  for (int i = 0; i < nodeNum; i++){
    temp = temp->GetNext();
  }
  return temp;
}
// Name: operator<<
// Desc: Allows you to cout a Schedule object
//       Overloaded << operator to return ostream from Schedule
//       Should not have any cout statements!
// Preconditions: Requires a Schedule sequence
// Postconditions: Returns ostream populated for each Item in Schedule
ostream &operator<< (ostream &output, Schedule &mySchedule){
  output << "WIP";
  return output;
}