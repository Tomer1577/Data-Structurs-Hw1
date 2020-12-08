#include <iostream>
#include "TwoList.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    TwoList mylist;
    TwoPair
    mylist.PushFront(1577,1678);
    TwoList::iterator iterbob = mylist.begin();
    TwoNode jiffy= *iterbob;
    int maybe = (jiffy.data);
    cout<<maybe<<endl;
    mylist.PopBack();
    return 0;
}
