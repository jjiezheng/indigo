#include "Scheduler.h"

#include "IUpdate.h"

static Scheduler* instance_ = nullptr;

Scheduler* Scheduler::instance() {
  if (!instance_) {
    instance_ = new Scheduler();
  }
  return instance_;
}

void Scheduler::scheduleUpdate(IUpdate *updater) {
  updaters_.push_back(updater);
}

void Scheduler::update(float dt) {
  for (IUpdate* updater : updaters_) {
    updater->update(dt);
  }
}