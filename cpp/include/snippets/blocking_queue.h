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
  boost::condition_variable_any cond;    // condition variable, to check whether queue empty or full
  std::vector<T> buffer;
};

#endif