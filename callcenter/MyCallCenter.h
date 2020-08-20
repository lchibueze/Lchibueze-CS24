#ifndef MYCALLCENTER_H
#define MYCALLCENTER_H

#include "CallCenter.h"

class MyCallCenter: public CallCenter {
  // Member Variables
  std::vector<Employee> mEmployees;
  std::vector<int> holdpool; 
  std::vector<int> priority_pool;
  std::map<int,Call*> mCalls;
  std::map<int,int> work; 
  

  struct Employee_Helper {
    Employee e;
    int next_call; // will store call ID for next call, will equal zero if no next call
  };

  std::vector<Employee_Helper> mHelper;
  

public:
  // Constructor
  MyCallCenter(std::vector<Employee> employees);
  // Destructor?
  ~MyCallCenter ();

  // Required Member Functions
  std::vector<int> calls(int minute, const std::vector<int>& call_ids);
  void learn(int minute, const std::vector<Call>& calls);

 

  // Other Member Functions

  //std::vector<Employee> skillset_priority();

  //std::vector<Employee>employee_call_importance();

// function will return a list of employees who can answer to a call with  their skill level higher than or equal to a call difficulty
  static bool orderSkill (const Employee_Helper &a, const Employee_Helper &b);

  //static bool orderImportance (const Employee_Helper &a, const Employee_Helper &b);

  static bool holdpoolImp (std::pair<int,Call*> &a, std::pair<int,Call*> &b);

  int find_call(int call_id); 

  int find_priority_call(int call_id);

  //int get_mCallsImp(int call_id);

  Call* getDefaultCall();

  void update_call();



  //std::vector<Employee> find_helpful_employee(int call_difficulty);

};

#endif
