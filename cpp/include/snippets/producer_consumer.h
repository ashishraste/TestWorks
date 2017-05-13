#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

/**
 * @brief      Class for producer.
 */
template<typename T>
class Producer
{
public:
  explicit Producer(boost::shared_ptr<T> buf, int interval=1, int nElements=10):
    pbuf(boost::shared_ptr<T>(buf)),
    period(interval),
    numElements(nElements)
  {}
  explicit Producer(T* buf, int interval=1, int nElements=10):
    pbuf(boost::shared_ptr<T>(buf)),
    period(interval),
    numElements(nElements)
  {}
  explicit Producer(): pbuf(),period(1),numElements(10)
  {}
  /**
   * @brief      Enqueues random integers to a buffer.
   */
  volatile void produce()
  {
    for (int i=0; i<numElements; ++i) {
      int element = std::rand() % 100;
      pbuf->insert(element);
      std::cout << "produced " << element << "\n";
      wait();
    }
  }

private:
  boost::shared_ptr<T> pbuf;
  int period;                       // time period, in seconds, to wait before producing a new element
  int numElements;                  // number of elements to produce
  void wait()
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{period});
  }
};


/**
 * @brief      Class for consumer.
 */
template<typename T>
class Consumer
{
public:
  explicit Consumer(boost::shared_ptr<T> buf, int interval=2, int nElements=10):
    cbuf(boost::shared_ptr<T>(buf)),
    period(interval),
    numElements(nElements)
  {}
  explicit Consumer(T* buf, int interval=2, int nElements=10):
    cbuf(boost::shared_ptr<T>(buf)),
    period(interval),
    numElements(nElements)
  {}
  explicit Consumer(): cbuf(),period(2),numElements(10)
  {}
  /**
   * @brief      Consumes elements from a buffer and prints them.
   */
  template<typename Y>
  volatile void consume()
  {
    for (int i=0; i<10; ++i) {
      Y element = cbuf->remove();
      std::cout << "consumed " << element << "\n";
      wait();
    }
  }

private:
  boost::shared_ptr<T> cbuf;
  int period;
  int numElements;
  void wait()
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{period});
  }
};


#endif