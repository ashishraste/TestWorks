#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <vector>

template<typename T>
class BlockingQueue
{
public:
  explicit BlockingQueue(const std::vector<T>& buf): buffer(buf)
  {}
  explicit BlockingQueue(): buffer()
  {}
  void insert(T elem);
  T remove();
  int size() { return buffer.size(); }
  ~BlockingQueue()
  {
    buffer.clear();                       // not sure if this is required
  }

private:
  boost::mutex mutex;                     // mutex variable
  boost::condition_variable_any cond;     // condition variable, to check whether the queue is empty and to release the mutex after inserting an element
  std::vector<T> buffer;
};

template<typename T>
void BlockingQueue<T>::insert(T elem) 
{
  boost::lock_guard<boost::mutex> lock(mutex);
  buffer.push_back(elem);
  cond.notify_all();                     // notifies all the waiting threads which are blocked on the queue  
  cond.wait(mutex);                      // here we can be sure that the mutex is released and the thread waits for a notification to lock the mutex
}

template<typename T>
T BlockingQueue<T>::remove()
{
  boost::lock_guard<boost::mutex> lock{mutex};
  while (buffer.size() == 0)
    cond.wait(mutex);                    // waits for the queue to get filled and for a notification to consume
  T elem = buffer.front();
  buffer.erase(buffer.begin());
  cond.notify_all();                     // notifies other threads after consumption which are blocked on the queue, wait() isn't required
  return elem;
}

#endif