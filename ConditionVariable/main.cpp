#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void fun1() {
    int count = 10;
    while(count > 0){
        std::unique_lock<std::mutex> locker(mu);
        q.push_back(count);
        locker.unlock();
        cond.notify_one(); // Notify one waiting thread, if there is one
        // cond.notify_all(); // wakes all waiting threads
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;
    }
}

void fun2() {
    int data = 0;
    while(data != 1){
        std::unique_lock<std::mutex> locker(mu);
       // if(!q.empty()) {
            // 1: checking is done continuously - inefficient => 2
            cond.wait(locker, []() { return !q.empty(); }); // added a predicate against spurious wake
            data = q.back();
            q.pop_back();
            locker.unlock();
            std::cout << "t2 got a value from t1: " << data << "\n";
       // } else{
            locker.unlock();
            // 2: if the deque is empty the thread takes a nap
           // std::this_thread::sleep_for(std::chrono::milliseconds(10));
       // }
    }
}

int main() {

    std::thread t1(fun1);
    std::thread t2(fun2);
    t1.join();
    t2.join();

    return 0;
}