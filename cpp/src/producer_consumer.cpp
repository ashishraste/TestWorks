#include <iostream>
#include <boost/thread.hpp>
#include "snippets/producer_consumer.h"
#include "snippets/blocking_queue.h"

using namespace std;

/**
 * @brief      Simple demo with two producers and two consumers, each sharing a blocking queue.
 */
int main()
{
  vector<int> integers;
  boost::shared_ptr<BlockingQueue<int>> queue(new BlockingQueue<int>(integers,10));
  Producer<BlockingQueue<int>> p1(queue);
  Producer<BlockingQueue<int>> p2(queue);
  Consumer<BlockingQueue<int>> c1(queue);
  Consumer<BlockingQueue<int>> c2(queue);
  
  srand(time(NULL));
  boost::thread pt1(boost::bind(&Producer<BlockingQueue<int>>::produce,p1));
  boost::thread pt2(boost::bind(&Producer<BlockingQueue<int>>::produce,p2));
  boost::thread ct1(boost::bind(&Consumer<BlockingQueue<int>>::consume<int>,c1));
  boost::thread ct2(boost::bind(&Consumer<BlockingQueue<int>>::consume<int>,c2));
  pt1.join();
  pt2.join();
  ct1.join();  
  ct2.join();
}