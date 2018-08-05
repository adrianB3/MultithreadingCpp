#include <iostream>
#include <future>

std::mutex mu;
std::condition_variable cond;

int factorial(std::future<int> &f){
    int res = 1;

    int N = f.get(); // if the promise is not fulfilled --> std::future_errc::broken_promise :(
    for (int i = N; i > 1; i--) {
        res *= i;
    }

    std::cout << "Result: " << res << "\n";

    return res;
}


int main() {

    int x;
    std::promise<int> p; // make a promise
    std::future<int> f = p.get_future(); // that will be fulfilled in the future
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f)); // get to work

    // do something else
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // maybe take a nap
    // If cannot fulfill promise
    p.set_exception(std::make_exception_ptr(std::runtime_error("To forget is human")));
    // p.set_value(4); // keeping my promise --> send the value

    x = fu.get(); // get the result

    std::cout << "From child thread: " << x << "\n";

    return 0;
}