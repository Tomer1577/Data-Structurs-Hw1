#include <iostream>
#include "TwoList.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    TwoList mylist;
    mylist.PushFront(1577,1678);

    cout<<"i am there"<<endl;
    TwoList::iterator iterbob = mylist.begin();
    cout<< " i a m after iter111"<<endl;
    TwoNode jiffy= *iterbob;
    cout<< " i a m after iter"<<endl;
    int maybe = (jiffy.data).classId;
    
    cout<<"i am here "<<maybe<<endl;
    //mylist.PopBack();
    return 0;
}
