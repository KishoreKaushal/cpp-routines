#include "stoppable_task.hpp"
#include <iostream>
#include <memory>

class Speak : public StoppableTask {
    int count;
public:
    Speak() : count(0), StoppableTask() {}

    Speak(const Speak&) = delete;
    Speak& operator=(const Speak&) = delete;

    void run() override {
        std::cout << ++count << " -- speaking ... " << std::endl;
    }
};

int main() {
    int i = 10;

    std::unique_ptr<Speak> spk = std::make_unique<Speak>();

//    spk->request_stop();
    do {
        (*spk)();
        if (--i <= 0) {
            spk->request_stop();
        }
    } while(not spk->is_stop_requested());

    return 0;
}