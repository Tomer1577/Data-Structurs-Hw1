#include <iostream>
#include "TwoList.h"
#include "library.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    TwoList mylist;
    shared_ptr<TwoNode> manode =  mylist.PushFront(1577,1678);
    TwoList::iterator iterbob = mylist.begin();
    TwoNode jiffy= *iterbob;
    int maybe = (jiffy.data).courseId;
    cout<<"here is course id: "<<maybe<<endl;
    mylist.PopPtr(manode);
    
    return 0;
}
