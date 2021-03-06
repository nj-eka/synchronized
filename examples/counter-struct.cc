#include <iostream>
#include <thread>
#include "../synchronized.hpp"

#define ITERATIONS 1000000

using namespace synchronized;

struct Counter {
    unsigned counter;
    explicit Counter(unsigned counter) : counter{counter} {}
};

void foo(synchronized<Counter>& syncCounter) {
    for (unsigned i = 0; i < ITERATIONS; i++) {
        ++syncCounter->counter;
    }
}

void bar(synchronized<Counter>& syncCounter) {
    for (unsigned i = 0; i < ITERATIONS; i++) {
        syncCounter->counter++;
    }
}

int main() {
    auto syncCounter = make_synchronized<Counter>(0);
    std::thread helper1 {foo, std::ref(syncCounter)};
    std::thread helper2 {bar, std::ref(syncCounter)};
    helper1.join();
    helper2.join();
    std::cout << syncCounter->counter << std::endl;
    return 0;
}
