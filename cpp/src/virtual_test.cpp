#include <stdio.h>
#include <iostream>
using namespace std;

/**
 * @brief     Short snippet on when (not) to use 'virtual'.
 * details    Identify why the below code won't compile.
 */
class A {
  template<class T>
  virtual void describe(T) { std::cout << sizeof(T) << std::endl; }
};

int main()
{
  A* a = new A();
  return 0;
}