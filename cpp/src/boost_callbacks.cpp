#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace std;

class ClassWithCallback
{
public:
	ClassWithCallback(){}
	void setCallback(boost::function<int(int)> const &cb) {
		callback_ = cb;
	}

	void executeCallback(int num) {
		callback_(num);
	}
private:
	boost::function<int(int)> callback_;
};

class DummyClass {
public:
	int dummyFunction(int i) {
		cout << "called as callback? " << i << "\n";
		return i;
	}
};

int main(int argc, char** argv)
{
	ClassWithCallback *cc = new ClassWithCallback();
	DummyClass dc;
	cc->setCallback(boost::bind(&DummyClass::dummyFunction,&dc,_1));
	cc->executeCallback(2);
	return 0;
}