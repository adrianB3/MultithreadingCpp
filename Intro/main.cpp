#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

void call_from_thread(){
    std::cout << "Beauty is only skin-deep" << std::endl;
    for(int i = 0; i < 10; i++){
        std::cout << i << std::endl;
        std::this_thread::sleep_for(1s);
    }
}
int main() {
    std::thread t1(call_from_thread); // thread 1 starts running
    //t1.join(); // main thread waits for thread 1 to finish
    //t1.detach(); // t1 will run on it's own -- daemon process

    //... some magic happening

    std::cout << t1.get_id() << std::endl;
    t1.join();
    std::cout << "Main thread here" << std::endl;
    std::this_thread::sleep_for(5s);
    //if(t1.joinable()) // check if joinable
      //  t1.join(); // crash , once detached a child thread remains forever detached
    return 0;
}