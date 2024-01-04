/**
 * @brief Observer notified by a Subject.
 * @details Observer is the object that executes behaviour
 * based on if the Subject it is attached to notifies it.
 * @author Jun Shao
 */

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
  public:
    virtual void notify() = 0;
};

#endif
