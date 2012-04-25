#ifndef Scheduler_H_
#define Scheduler_H_

#include <vector>

class IUpdate;

class Scheduler {
  
public:
  
  static Scheduler* instance();
  
public:
  
  void scheduleUpdate(IUpdate* updater);
  
  void update(float dt);
  
private:
  
  Scheduler() = default;
  
private:
  
  std::vector<IUpdate*> updaters_;
  
};

#endif
