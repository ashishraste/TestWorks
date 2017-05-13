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
    buffer.clear();
  }

private:
  boost::mutex mutex;                    // mutex variable
  boost::condition_variable_any cond;    // condition variable, to check whether the queue is empty or full
  std::vector<T> buffer;
};

template<typename T>
void BlockingQueue<T>::insert(T elem) 
{
  boost::unique_lock<boost::mutex> lock(mutex);
  buffer.push_back(elem);
  cond.notify_all();                     // notifies all the waiting threads   
  cond.wait(mutex);                      // releases the mutex and waits for notification to lock again
}

template<typename T>
T BlockingQueue<T>::remove()
{
  boost::unique_lock<boost::mutex> lock{mutex};
  while (buffer.size() == 0)
    cond.wait(mutex);                    // waits for the queue to get filled and for a notification to consume
  T elem = buffer.front();
  buffer.erase(buffer.begin());
  cond.notify_all();                     // notifies other threads after consumption
  return elem;
}

#endif