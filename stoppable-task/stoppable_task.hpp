#ifndef STOPPABLE_TASK_HPP
#define STOPPABLE_TASK_HPP

#include <future>

class StoppableTask {
    std::promise<void>  exit_signal;
    std::future<void>   future_obj;

public:

    StoppableTask() : future_obj(exit_signal.get_future()) {}

    StoppableTask(const StoppableTask&) = delete;
    
    StoppableTask& operator=(const StoppableTask&) = delete;

    virtual void run() = 0;

    virtual void operator()() {
        run();
    }

    bool is_stop_requested(int timeout_in_ms = 0) const {
        std::chrono::milliseconds t(timeout_in_ms);
        return (future_obj.wait_for(t) == std::future_status::ready);
    }

    void request_stop() {
        exit_signal.set_value();
    }
};

#endif