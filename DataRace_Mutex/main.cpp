#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mu;  // var used for mutual exclusion --> like a binary semaphore

void shared_print(string const msg, int id){
    lock_guard<mutex> guard(mu); // RAII
   // mu.lock(); // stdout is sync with mutex mu
    cout << msg << id << endl;
   // mu.unlock();
}

void fun(){
    for (int i = 0; i > -100; --i) {
        shared_print(string("from t1: "), i);
    }
}
int main() {
    thread t1(fun);

    for(int i = 0; i < 100; i++){
        shared_print(string("from main: "), i);
    }
    // main and t1 threads are racing for the stdout resource
    t1.join();
    return 0;
}