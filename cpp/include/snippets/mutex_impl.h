#ifndef MUTEX_IMPL_H
#define MUTEX_IMPL_H

#include <pthread.h>

class MutexCore
{
public:
  explicit MutexCore(): mutex() 
  {}
  pthread_mutex_t mutex;
};

class Mutex
{
public:
  explicit Mutex(): pmc(new MutexCore())
  {
    pthread_mutex_init(&(pmc->mutex),NULL);
  }
  virtual ~Mutex()
  {
    pthread_mutex_destroy(&(pmc->mutex));
    delete pmc;
  }
  void lock()
  {
    pthread_mutex_lock(&(pmc->mutex));
  }
  void unlock()
  {
    pthread_mutex_unlock(&(pmc->mutex));
  }

private:
  MutexCore *pmc;
};

#endif