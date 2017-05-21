#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <vector>
#include <cassert>

template<typename T>
class BlockingQueue
{
public:
  explicit BlockingQueue(const std::vector<T>& buf): 
    buffer(buf)
  {}
  explicit BlockingQueue(): buffer()
  {}
  void insert(const T& elem);
  T remove();
  int size() const { return buffer.size(); }
  ~BlockingQueue()
  {}

private:
  boost::mutex mutex;                             // mutex variable
  boost::condition_variable_any notEmptyCond;     // condition variable, to check whether the queue is empty
  std::vector<T> buffer;
};

template<typename T>
void BlockingQueue<T>::insert(const T& elem) 
{
  boost::mutex::scoped_lock lock(mutex);
  buffer.push_back(elem);
  notEmptyCond.notify_one();                      // notifies one of the waiting threads which are blocked on the queue  
  assert(!buffer.empty());
}

template<typename T>
T BlockingQueue<T>::remove()
{
  boost::mutex::scoped_lock lock(mutex);
  while (buffer.empty()) {
    std::cout << "waiting to consume at least one element \n";
    notEmptyCond.wait(lock,[&](){ return (buffer.size() > 0); });   // waits for the queue to get filled and for a notification to consume
  }
  T elem = buffer.front();
  buffer.erase(buffer.begin());
  return elem;
}

#endif