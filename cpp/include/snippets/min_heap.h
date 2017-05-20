#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <math.h>
#include <vector>

/**
 * @brief      Class for minimum heap.
 *
 * @tparam     T  numerical values stored in the min-heap.
 */
template<typename T>
class MinHeap
{
public:
  explicit MinHeap(): heap()
  {}
  void insert(T elem);
  T deleteMin();
  T peek();
  std::vector<T> getHeap();

private:
  std::vector<T> heap;
  void siftUp();
  void siftDown(int pidx);
};

template<typename T>
void MinHeap<T>::siftUp()
{
  if (heap.size() == 1) return;
  int cidx = heap.size()-1;
  int pidx = floor((cidx-1)/2);
  T parent = heap.at(pidx);
  T child = heap.at(cidx);
  while (parent > child) {                                      // swap values, update parent/child indices and their new values
    heap.at(cidx) = parent;
    heap.at(pidx) = child;
    cidx = pidx;
    pidx = floor((cidx-1)/2);
    parent = heap.at(pidx);
    child = heap.at(cidx);
  }
}

template<typename T>
void MinHeap<T>::siftDown(int pidx)
{
  if (heap.size() <= 1) return;                                 
  int c1idx = pidx * 2 + 1;
  int c2idx = pidx * 2 + 2;
  if (c1idx > heap.size()-1 && c2idx > heap.size()-1) return;   // no more child elements to compare
  int cidx;
  if (c2idx > heap.size()-1)                                    // if there is only one child
    cidx = c1idx; 
  else {                                                        // consider the minimum of the child elements
    T c1 = heap.at(c1idx);
    T c2 = heap.at(c2idx);
    cidx = (c1 < c2 ? c1idx : c2idx);
  }
  T child = heap.at(cidx);
  T parent = heap.at(pidx);
  if (parent > child) {                                         // recursive sift-down
    heap.at(cidx) = parent;
    heap.at(pidx) = child;
    pidx = cidx;
    siftDown(pidx);
  }
  return ;
}

template<typename T>
void MinHeap<T>::insert(T elem)
{
  heap.push_back(elem);
  siftUp();
}

template<typename T>
T MinHeap<T>::deleteMin()
{
  if (!heap.size()) return -1;
  T delElem = heap.at(0);
  heap.at(0) = heap.at(heap.size()-1);
  heap.pop_back();
  if (heap.size()) siftDown(0);
  return delElem;
}

template<typename T>
T MinHeap<T>::peek()
{
  if (!heap.size()) return -1;
  else return heap.at(0);
}

template<typename T>
std::vector<T> MinHeap<T>::getHeap()
{
  return heap;
}

#endif