#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

// More realistic example
class Logger {
private:
    mutex m_mutex;
    ofstream f;
public:
    Logger(){
        f.open("log.txt");
    }
    void shared_print(string id, int value){
        lock_guard<mutex> locker(m_mutex);
        f << "from : " << id << " : " << value << endl;
        cout << "from : " << id << " : " << value << endl;
    }

    // ! Never pass the protected resource to the outside world
};

mutex mu;  // var used for mutual exclusion --> like a binary semaphore

void shared_print(string const msg, int id){
    // however, neither lock_guard is sufficient as the mutex must be bound to the
    // resource it protects
    lock_guard<mutex> guard(mu); // RAII
    // mu.lock(); // stdout is synchronized using mutex mu
    // using mutex this way is not recommended
    // because if the code between the locks throws an exception
    // the thread is locked forever
    // --> solution is to use lock_guard
    cout << msg << id << endl;
    // mu.unlock();
}

void fun(Logger &log){
    for (int i = 0; i > -100; --i) {
        log.shared_print(string("from t1: "), i);
    }
}
int main() {
    Logger log;
    thread t1(fun, ref(log));

    for(int i = 0; i < 100; i++){
        log.shared_print(string("from main: "), i);
    }
    // main and t1 threads are racing for the stdout resource
    t1.join();
    return 0;
}