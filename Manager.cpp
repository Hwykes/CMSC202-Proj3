#include "Manager.h"

// Name: Manager (constructor)
// Desc: Creates a Manager to manage schedules 
// Preconditions:  None
// Postconditions: A manager is created to populate m_schedules
Manager::Manager(string fileName){
  m_fileName = fileName;
  ReadFile();
  MainMenu();
}
// Name:  Manager (destructor)
// Desc: Deallocates all dynamic aspects of a Manager
// Preconditions: There is an existing Schedule
// Postconditions: All schedules are cleared
Manager::~Manager(){
  cout << "Schedules removed from memory" << endl;
  for (int i = 0; i < (int)m_schedules.size(); i++){
      Item* curr = m_schedules.at(i)->GetData(0);
      Item* ptr = curr;
      while (curr != nullptr){
      ptr = curr;
      curr = curr->GetNext();
      delete ptr;
    }
    ptr = nullptr;
    curr = nullptr;
  }
}
// Name:  DisplaySchedules
// Desc: Displays each schedule in m_schedules
// Preconditions: At least one schedule is in m_schedules
// Postconditions: Displays all items in a schedule for all schedules in m_schedules
void Manager::DisplaySchedules(){
  for (int i = 0; i < (int)m_schedules.size(); i++){
    if (m_schedules.at(0) == nullptr){
      cout << "There are no schedules" << endl;
    }
    else{
      cout << "Schedule for " << m_schedules.at(i)->GetName() << endl;
      for (int j = 0; j < (int)m_schedules.at(i)->GetSize(); j++){
        Item* neededItem = new Item;
        neededItem = m_schedules.at(i)->GetData(j);
        cout << neededItem->GetTime() << "  :  " << neededItem->GetName() << endl;
      }
      cout << endl;
    }
  }
}
// Name:  ReadFile
// Desc: Reads in a file that has the schedule name then semicolon the starting time then a semicolon
//       then the name of the activity.
//       Input files are an indeterminate length. There are an indeterminate number of schedules in
//       an input file. There are an indeterminate number of items in each file.
//       The vector can hold many schedules.
// Preconditions: Valid file name of schedules
// Postconditions: Populates each schedule and puts in m_schedules
void Manager::ReadFile(){
  int nodes = 0;
  int schedules = 0;
  string scheduleName, startingTime, activityName;
  string scheduleName2 = " ";
  const char DELIMITER = ';';
  ifstream myFile(m_fileName);
  if(myFile.is_open()){
    while (myFile){
      bool isFound = false;
      getline(myFile, scheduleName, DELIMITER);
      getline(myFile, startingTime, DELIMITER);
      getline(myFile, activityName);
      int time = stoi(startingTime, nullptr); 
      Item *newItem = new Item(activityName, time);
      for (int i = 0; i < (int)m_schedules.size(); i++){
        if (m_schedules.at(i)->GetName() == scheduleName){
          m_schedules.at(i)->InsertSorted(newItem);
          isFound = true;
        }
      }
      if (isFound == false){
        Schedule *newSchedule = new Schedule(scheduleName);
        newSchedule->InsertSorted(newItem);
        m_schedules.push_back(newSchedule);
        schedules++;
      }
      nodes++;
    }
    cout << nodes << " nodes loaded across " << schedules << " schedules" << endl;
  }
  else{
    cout << "Unable to open file" << endl;
  }
  myFile.close();
}
// Name: InsertNewItem
// Desc: Asks the user which schedule they would like to insert into (uses FindSchedule)
//       If new schedule, inserts a new schedule and indicates a new schedule was created
//       Prompts user for time and name of item then inserts item into schedule
// Preconditions: Populated m_schedules
// Postconditions: Either inserts into existing schedule or inserts into a new schedule
void Manager::InsertNewItem(){
  string schedName;
  int schedTime;
  string activityName;
  int schedIndex;
  int notFound = -1;
  int latestTime = 2400;
  cout << "What is the name of the schedule you would like to insert into? ";
  cin >> schedName;
  cout << "What is the start time of the activity? ";
  cin >> schedTime;
  while (schedTime < 0 || schedTime > latestTime){
    cout << "What is the start time of the activity? ";
    cin >> schedTime;
  }
  cout << "What is the name of the activity? ";
  cin >> activityName;
  Item *newItem = new Item(activityName, schedTime);
  schedIndex = FindSchedule(schedName);
  if (schedIndex == notFound){
      Schedule *newSchedule = new Schedule(schedName);
      newSchedule->InsertSorted(newItem);
      m_schedules.push_back(newSchedule);
  }
  else{
    m_schedules.at(schedIndex)->InsertSorted(newItem);
  }
}
// Name: FindSchedule
// Desc: Returns the index of the schedule from m_schedules else -1
// Preconditions: Populated m_schedules
// Postconditions: Returns the index of schedule with the matching name or it returns -1
int Manager::FindSchedule(string schedName){
  int schedNum;
  for (int i = 0; i < (int)m_schedules.size(); i++){
    if (m_schedules.at(i)->GetName() == schedName){
      schedNum = i;
      return schedNum;
    }
    else{
      schedNum = -1;
    }
  }
  return schedNum;
}
// Name:  MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_schedules
// Postconditions: None
void Manager::MainMenu(){
  int choice = 0;
  while (choice != 4){
    cout << "What would you like to do?" << endl;
    cout << "1. Display Schedules" << endl;
    cout << "2. Reverse Schedules" << endl;
    cout << "3. Insert New Item" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;
    if (choice == 1){
      DisplaySchedules();
    }
    else if (choice == 2){
      ReverseSchedule();
    }
    else if (choice == 3){
      InsertNewItem();
    }
  }
}
  // Name: ReverseSchedule
  // Desc: User chooses a schedule and the schedule is reversed
  //       If only one schedule in m_schedules, automatically reverses it without prompting the user
  // Preconditions: Populated m_schedules
  // Postconditions: Reverses a specific schedule replacing in place
  void Manager::ReverseSchedule(){
    string schedName;
    int minSched = 1;
    bool isFound = false;
    if ((int)m_schedules.size() == minSched){
      m_schedules.at(0)->ReverseSchedule();
      return;
    }
    else{
      while (isFound == false){
        cout << "What schedule would you like to reverse? ";
        cin >> schedName;
        for (int i = 0; i < (int)m_schedules.size(); i++){
          if (m_schedules.at(i)->GetName() == schedName){
            m_schedules.at(i)->ReverseSchedule();
            isFound = true;
          }
        }
      }
    }
  }