#ifndef STOPPABLE_TASK_HPP
#define STOPPABLE_TASK_HPP

#include <future>

enum class TaskState : unsigned char {
    Ready = 0,
    Executing = 1,
    Terminating = 2
};

class StoppableTask {
    std::promise<void>  exit_signal;
    std::future<void>   future_obj;

protected:
    TaskState           task_state;
    virtual void run() = 0;

public:

    StoppableTask() 
    :   future_obj(exit_signal.get_future()), 
        task_state(TaskState::Ready) {}

    StoppableTask(const StoppableTask&) = delete;
    
    StoppableTask& operator=(const StoppableTask&) = delete;

    virtual void operator()() {
        task_state = TaskState::Executing;
        run();
    }

    bool is_stop_requested(int timeout_in_ms = 100) const {
        std::chrono::milliseconds t(timeout_in_ms);
        return (future_obj.wait_for(t) == std::future_status::ready);
    }

    void request_stop() {
        task_state = TaskState::Terminating;
        exit_signal.set_value();
    }

    TaskState get_task_state() {
        return task_state;
    }
};

#endif