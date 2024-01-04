/**
 * @brief Subject for an Observer.
 * @details Subject encapsulates the behaviour Observer objects are dependent on
 * and is able to notify Observer objects without depending on their types.
 * @author Jun Shao
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <algorithm>
#include "../main/Observer.h"

class Subject
{
public:
  void attach(Observer *);
  void detach(Observer *);
  ~Subject();

protected:
  void notify();

private:
  std::vector<Observer *> _observers;
};

#endif
