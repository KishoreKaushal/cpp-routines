#ifndef STOPPABLE_TASK_HPP
#define STOPPABLE_TASK_HPP

#include <future>

class StoppableTask {
    std::promise<void>  exit_signal;
    std::future<void>   future_obj;

public:

    StoppableTask();

    StoppableTask(const StoppableTask&) = delete;
    
    StoppableTask& operator=(const StoppableTask&) = delete;

    virtual void run() = 0;

    virtual void operator()();

    bool is_stop_requested(int timeout_in_ms = 0) const;

    void request_stop();
};

#endif