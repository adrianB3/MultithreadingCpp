#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class Logger {
private:
    std::mutex _mu;
    std::once_flag _flag;
    std::ofstream _f;
public:
    Logger(){
    }

    void shared_print(std::string id, int value){
        //std::unique_lock<std::mutex> locker(_mu); // unique_lock is more flexibile than lock_guard
        //if(!_f.is_open()){                          // but with more overhead
        //    _f.open("log.txt");
        //}
        // --> Thread safe but the file is opened by multiple threads
        // the opening of the file should be done once
        // also the file it's open only when needed so it's lazy initialized
        // =>
        std::call_once(_flag, [&](){ _f.open("log.txt"); }); // lambda expr
        std::unique_lock<std::mutex> locker(_mu);
        _f << "From " + id + " : " << value << std::endl;
        std::cout << "From " + id + " : " << value << std::endl;
    }
};


int main() {
    Logger log;
    std::thread th1([&](){
       for(int i = 0; i < 100; i++)
           log.shared_print("th1", i);
    });

    std::thread th2([&](){
        for(int i = 0; i < 100; i++)
            log.shared_print("th2", i);
    });

    th1.join();
    th2.join();

    return 0;
}