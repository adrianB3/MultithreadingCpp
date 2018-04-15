#include <iostream>
#include <thread>
using namespace std;
void call_from_thread(){
    cout << "Beauty is only skin-deep" << endl;
}
int main() {
    thread t1(call_from_thread); // thread 1 starts running
    //t1.join(); // main thread waits for thread 1 to finnish
    //t1.detach(); // t1 will run on it's own -- daemon process

    //... some magic happening

    if(t1.joinable()) // check if joinable
        t1.join(); // crash , once detached a child thread remains forever detached
    return 0;
}