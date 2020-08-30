 #include "MyCallCenter.h"
#include <iostream>
#include <algorithm>
#include <vector>

CallCenter* CallCenter::create(std::vector<Employee> employees) {
  return new MyCallCenter(employees);
}

// MyCallCenter Member Functions
MyCallCenter::MyCallCenter(std::vector <Employee> employees){
  mEmployees = employees;
  //std::fill(mEmployees.id.begin(),mEmployees.id.end(),0);
  for (unsigned long i=0; i<mEmployees.size(); i++){
    work[mEmployees[i].id]=0;
    mEmployees[i].call=getDefaultCall();
    Employee_Helper temp;
    temp.e = mEmployees[i];
    temp.next_call = 0;
    mHelper.push_back(temp);


    //for debugging 
    printDebug = true;
  }
}


Call* MyCallCenter::getDefaultCall() {
  Call* temp = new Call ();
  temp->id = 0;
  temp->recieved = 0;        
  temp->importance = 0;      
  temp-> difficulty=0;      
  temp->work_required =0;   
  temp->work_performed=0;
  return temp;
}

bool MyCallCenter::orderSkill (const Employee_Helper &a, const Employee_Helper &b){
  return a.e.skill<=b.e.skill;
}

bool MyCallCenter::orderImportance (const Employee_Helper &a, const Employee_Helper &b){
  return a.e.call->importance<=b.e.call->importance;
} 

bool MyCallCenter::holdpoolImp(std::pair<int,Call*> &a, std::pair<int,Call*> &b){ 
  return a.second->importance<=b.second->importance;
}

bool MyCallCenter::findMcalls(int call_id){
  // std::map<int,Call*> mCalls;
  std::map<int, Call*>::iterator it;
  for(it = mCalls.begin(); it != mCalls.end(); it++){
    if(call_id == it->first){
      return true;
    }
  }

  return false;
}
int MyCallCenter::find_call (int call_id) {
  for (unsigned long i=0; i<holdpool.size(); i++){
    if (holdpool[i]==call_id)
      return i;
  }
  return -1;
}

int MyCallCenter::find_priority_call (int call_id) {
  for (unsigned long i=0; i<priority_pool.size(); i++){
    if (priority_pool[i]==call_id)
      return i;
  }
  return -1;

}


void MyCallCenter::update_call(){
  std::map<int,Call*>::iterator it;
  for (it=mCalls.begin();it!=mCalls.end();it++) {
    it->second->work_performed++;
  }
}

std::vector<int> MyCallCenter::calls(int minute, const std::vector<int>& call_idss) {
  std::vector<int> call_ids = call_idss;
  std::vector<int> accepted_learn_ids; 
  if (minute<540) { 
    if(printDebug)
      std::cout<< "Step 1" <<std::endl;
    //Step 1 - assigning next call to employee
    for (unsigned long i=0; i<mHelper.size(); i++){
      if((mHelper[i].e.call->id != 0) &&((mHelper[i].e.call->work_performed)==(mHelper[i].e.call->work_required+1))){
        work[mHelper[i].e.id]=-1;
      }
      else if((work[mHelper[i].e.id]==0) && (mHelper[i].next_call !=0)){
        work[mHelper[i].e.id] = mHelper[i].next_call;
        int find = find_priority_call(mHelper[i].next_call);
        if (find != -1) {
          priority_pool.erase(priority_pool.begin()+find);
          accepted_learn_ids.push_back(mHelper[i].next_call);
        }
        else {
          holdpool.erase(holdpool.begin()+find_call(mHelper[i].next_call));
        }
       
        mHelper[i].next_call = 0;
        
      }
    }

    //Step 2 - Find free employee for priority pool calls
    //std::sort(priority_pool.begin(), priority_pool.end()), std::greater<int>();
    if(printDebug)
      std::cout<< "Step 2" <<std::endl;
    int count =priority_pool.size()-1;
    
    if (count >=0) {
      unsigned long j = priority_pool.size()-1;
      while(j>0){
        if(printDebug)
          std::cout<<"value of j "<<j<<std::endl;
        //std::sort(mHelper.begin(), mHelper.end(),orderSkill);
        //code for algorithm of going back and forth with skillsets of employee
        int start=mHelper.size()/2;
        for (unsigned long i=0; i<mHelper.size(); i++){
          if (i%2==0) {
            if (count >= 0 && work[mHelper[start+i].e.id]==0) {
              work[mHelper[start+i].e.id] = priority_pool[j];
              accepted_learn_ids.push_back(priority_pool[j]);
              priority_pool.erase(priority_pool.begin()+j); 
              if(j != 0)
                j--;

              count--;
              start += i;
            }  
          }
          else {
            if (count >= 0 && work[mHelper[start-i].e.id]==0) {
              work[mHelper[start-i].e.id] = priority_pool[j];
              accepted_learn_ids.push_back(priority_pool[j]);
              priority_pool.erase(priority_pool.begin()+j); 
             
              if(j != 0)
                j--;
              count--;
              start -= i;
            } 
          }
        }
        if(printDebug)
          std::cout<<"value of j "<<j<<std::endl;
      }
    }
    
    if(printDebug)
      std::cout<< "Step 3" <<std::endl;   
    //Step 3 - finding employees with non important calls for priority pool calls
    unsigned long temp=0;
    if (count>0){
      for(unsigned long i=count;i>=0;i--){
        // std::sort(mHelper.begin(), mHelper.end(),orderImportance);
        while (temp<mHelper.size() && (((mHelper[temp].e.call->id) != (work[mHelper[temp].e.id])) || (work[mHelper[temp].e.id]!=-1))){
          temp++; 
          }
        if (temp<mHelper.size()){
          mHelper[temp].next_call=priority_pool[i];
          temp++; 
        }
        
      } 
    }
    if(printDebug)
      std::cout<< "Step 4" <<std::endl;
    //Step 4 - repeat step two and three for call ids
    //if (call_ids.size()>0){
    std::sort(call_ids.begin(), call_ids.end()), std::greater<int>();
    count =call_ids.size()-1;

    if (count>=0) {
      for (unsigned long j = count; j>0; j--) {
        //std::sort(mHelper.begin(), mHelper.end(),orderSkill);
        //code for algorithm of going back and forth with skillsets of employee
        int start=mHelper.size()/2;
        for (unsigned long i=0; i<mHelper.size(); i++){
          if (i%2==0) {
            if (work[mHelper[start+i].e.id]==0) {
              work[mHelper[start+i].e.id] = call_ids[j];
              accepted_learn_ids.push_back(call_ids[j]);
              //int *x=&j;
              call_ids.erase(call_ids.begin()+j); 
              start = start + i;
              count--;
            }
    
          }
          else {
            if (work[mHelper[start-i].e.id]==0) {
              work[mHelper[start-i].e.id] = call_ids[j];
              accepted_learn_ids.push_back(call_ids[j]);
              call_ids.erase(call_ids.begin()+j); 
              start = start -i;
              count--;
            } 
          }
         
        }
      }
    }

    temp=0; 
    if (count>0) {
      for(unsigned long i=count;i>0;i--){
      // std::sort(mHelper.begin(), mHelper.end(),orderImportance);
        while (temp<mHelper.size() && (((mHelper[temp].e.call->id) != (work[mHelper[temp].e.id])) || (work[mHelper[temp].e.id]!=-1))){
          temp++; 
        }
        if (temp<mHelper.size()){
          
          mHelper[temp].next_call=call_ids[i];
          temp++; 
        }
      }
    }

    if(printDebug)
      std::cout<< "Step 5" <<std::endl;
    //Step 5 - adding any unanswered calls from call ids to priority pool
    priority_pool.insert(priority_pool.end(),call_ids.begin(), call_ids.end());


    //stop receiving calls (adding calls to holdpool), finish up calls in holdpool until 600 min
    if(printDebug)
      std::cout<< "Step 6" <<std::endl;
    //Step 6 - find employees with skill level for calls in hold pool

  
    //std::sort(mCalls.begin(), mCalls.end(), holdpoolImp);
    // if (mCalls.size()>0) {
    //   for (unsigned long i=mCalls.size()-1; i>0; i--){
    //     int find = find_call(mCalls[i]->id);
    //     if (find!=-1)  { //if call_id is in holdpool
    //       //std::sort(mHelper.begin(), mHelper.end(), orderImportance);
    //       for (unsigned long j=0; j<mHelper.size(); j++) {
    //         if ((mHelper[j].e.skill>=mCalls[i]->difficulty) && (mCalls[work[mHelper[j].e.id]]->importance<mCalls[i]->importance)){
    //           if (work[mHelper[j].e.id] == 0) {
    //             work[mHelper[j].e.id] = mCalls[i]->id;
    //             break;
    //           }
    //           else if (mHelper[j].next_call==0) {
    //             mHelper[j].next_call = mCalls[i]->id;
    //             break;
    //           }
                
    //           }
    //         }

    //       }
    //     }
    //   } 

    if (holdpool.size()>0) {
      auto originalSize = holdpool.size();
      for (unsigned long i=holdpool.size()-1; i>=0; i--){
        if(i > originalSize){
          break;
        }

        int find = find_call(holdpool[i]);
        if (find!=-1)  { //if call_id is in holdpool
          //std::sort(mHelper.begin(), mHelper.end(), orderImportance);
          for (unsigned long j=0; j<mHelper.size(); j++) {
            bool first = (mHelper[j].e.skill>=mCalls[holdpool[i]]->difficulty) ;
            auto temppp = work[mHelper[j].e.id];
            auto find = findMcalls(temppp);
            if(temppp != 0 && find){
              auto one = mCalls[temppp]->importance; //segfault here
              auto two = mCalls[holdpool[i]]->importance;
              bool second = (one<two);
              if (first && second){
                if (work[mHelper[j].e.id] == 0) {
                  work[mHelper[j].e.id] = mCalls[holdpool[i]]->id;
                  break;
                }
                else if (mHelper[j].next_call==0) {
                  mHelper[j].next_call = mCalls[holdpool[i]]->id;
                  break;
                }
                  
                }
            }
            else if (first){
              work[mHelper[i].e.id] = holdpool[i];
              break;
            }
            }

          }
        }
      }

    }

  if(printDebug)
    std::cout<<"step7"<<std::endl;
  //return accepted_learn_ids;
  std::vector<int> temp;
  std::map<int,int>::iterator it;
  for (it=work.begin();it != work.end(); it++) {
    temp.push_back(it->second);
  }

  if(printDebug)
    std::cout<<"done with call function"<<std::endl;
  return temp;

}
  
 //for loops created for learn function to run through employees' id which is linked to call id 
void MyCallCenter::learn(int minute, const std::vector<Call>& callss) {
  std::vector<Call> calls = callss;
  if(minute){}
  if(printDebug)
      std::cout<<"getInfoCall"<<std::endl;
  for(unsigned long i=0; i<calls.size(); i++) { 
    // //ASSIGN RECEIVED = MINUTE FOR EACH CALL IN CALLS 
    // calls[i].recieved=minute;
    mCalls[calls[i].id] = new Call(calls[i]);
    
  }

    if(printDebug)
      std::cout<<"check"<<std::endl;
  //check to see if any employees are underqualified for the call they're currently on
  for(unsigned long i = 0; i<mHelper.size(); i++){
    if(mHelper[i].e.call != NULL && mHelper[i].e.call->difficulty > mHelper[i].e.skill){
      holdpool.push_back(mHelper[i].e.call->id); //add advanced call to hold pool
      mHelper[i].e.call = getDefaultCall();
      work[mHelper[i].e.id] = 0;
    }
  }

  if(printDebug)
      std::cout<<"calls"<<std::endl;
  for (unsigned long i=0; i<mHelper.size();i++){
    //DELETE DEFAULT CALL BEFORE ASSIGNING MCALLS
    if (work[mHelper[i].e.id]==-1) {
      work[mHelper[i].e.id]=0;
      delete mHelper[i].e.call;
      mHelper[i].e.call = getDefaultCall();
    }
    else if (work[mHelper[i].e.id] == 0){
      delete mHelper[i].e.call;
      mHelper[i].e.call = getDefaultCall();
    }
    else if ((mHelper[i].e.call->id==0) && (mCalls.find(work[mHelper[i].e.id])!=mCalls.end())){
      delete mHelper[i].e.call;
      mHelper[i].e.call = mCalls[work[mHelper[i].e.id]];
    }
    else if ((mHelper[i].e.call->id!=0) && (mHelper[i].next_call!=0)){
      
      holdpool.push_back(mHelper[i].e.call->id);
      work[mHelper[i].e.id]=0;
      mHelper[i].e.call = getDefaultCall();
     // mHelper[i].e.call = mCalls[work[mHelper[i].e.id]];
    }
    else
      mHelper[i].e.call->work_performed++;
  }
}


/*std::vector<Employee> MyCallCenter::skillset_priority (){
  std::vector<Employee> temp;
  for (const Employee& e:mEmployees) {
    temp.push_back(e);
  }
  std::sort(temp.begin(),temp.end(), orderSkill);
  return temp; 
}

std::vector<Employee> MyCallCenter::employee_call_importance(){
  std::vector<Employee> temp;
  for (const Employee& e:mEmployees) {
    temp.push_back(e);
  }
  std::sort(temp.begin(),temp.end(), orderImportance);
  return temp; 
}*/
MyCallCenter::~MyCallCenter() {}
