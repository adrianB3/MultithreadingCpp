#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class Logger {
private:
    std::mutex _mu;
    std::ofstream _f;
public:
    Logger(){
        _f.open("log.txt");
    }
    void shared_print(std::string id, int value){
        std::lock_guard<std::mutex> locker(_mu);
        std::cout << "From " + id + " : " << value << "\n";
    }
};

void a_thread(Logger &log){
    for (int i = 0; i > -100; i--) {
        log.shared_print("thread1", i);
    }
}

int main() {
    Logger log;

    std::thread thread1(a_thread, std::ref(log));

    for (int i = 0; i < 100; i++) {
        log.shared_print("main", i);
    }

    /// TODO it

    thread1.join();
    return 0;
}