#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include "Scheduler.h"

class MyScheduler: public Scheduler {
  // Member Variables
public:
  // Constructor
  // Destructor?

  // Required Member Function
  std::vector<Shipment> schedule();
};

#endif
