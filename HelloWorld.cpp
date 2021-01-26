#include <iostream>
#include "SampleClass.h"
using namespace std;

int main(int argc, char **argv) {
	cout << "Hello world";
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    SampleClass obj;
    obj.print();
	return 0;
}
