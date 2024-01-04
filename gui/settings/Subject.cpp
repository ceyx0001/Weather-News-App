#include "Subject.h"

using std::find;
using std::vector;

/**
 * @brief Default destructor.
 * @details Default destructor for Subject but does not do anything.
 * @return Nothing.
 */
Subject::~Subject() {}

/**
 * @brief Attach Observer.
 * @details Attaches an Observer to Subject by adding it to
 * the internal list of Observer objects.
 * @param o is the pointer to the Observer.
 * @return Nothing.
 */
void Subject::attach(Observer *o)
{
  if (find(_observers.begin(), _observers.end(), o) == _observers.end())
    this->_observers.push_back(o);
}

/**
 * @brief Detach Observer.
 * @details Detaches an Observer to Subject by removing it from
 * the internal list of Observer objects.
 * @param o is the pointer to the Observer.
 * @return Nothing.
 */
void Subject::detach(Observer *o)
{
  vector<Observer *>::iterator it;

  it = find(_observers.begin(), _observers.end(), o);

  if (it != _observers.end())
    _observers.erase(it);
}

/**
 * @brief Attach observer.
 * @details Attaches an Observer to Subject by adding it to a list
 * of Observer objects.
 * @param o is the pointer to the Observer.
 * @return Nothing.
 */
void Subject::notify()
{
  vector<Observer *>::iterator it;

  for (it = _observers.begin(); it != _observers.end(); ++it)
    (*it)->notify();
}
