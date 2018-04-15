#include <iostream>
#include <thread>
using namespace std;

class Fctor{
public:
    void operator ()(string &msg) {
        cout <<"t1 says: " << msg << endl;
        msg = "He who thinks great thoughts, often makes great errors."; // inf at ref changed
    }
};

int main() {
    string s = "Where there is no trust, there is no love.";
    //thread t1((Fctor()), ref(s)); // t1 starts running , msg passed by reference
    // RAII --> wrapper w(t1)

    /*try {

            cout << "from main: " << s << endl;

    } catch (...) {
        t1.join();
        throw ;
    }*/

   // t1.join();
    //cout << "from main: " << s << endl;

    // another way
    /*thread t1((Fctor()), move(s));
    thread t2 = move(t1);
    t2.join();*/


    /*cout << this_thread::get_id() << endl;
    cout << t1.get_id();
    t1.join();*/

    // Avoid oversubscribing (creating more threads than that are hardware supported --> because of contact switching
    cout << thread::hardware_concurrency() << endl; // no of threads that can truly run concurrently


    return 0;
}