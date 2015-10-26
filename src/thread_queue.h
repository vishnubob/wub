#ifndef _AUDIO_QUEUE_H
#define _AUDIO_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadQueueException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Queue is not running!";
    }
};

static ThreadQueueException _thread_queue_exception;

template <class T>
class ThreadQueue
{
public:
    ThreadQueue() : _running(true) {}

    void enqueue(T item)
    {
        std::lock_guard<std::mutex> lock(_que_lock);
        _que.push(item);
        _que_condition.notify_one();
    }

    T dequeue()
    {
        std::unique_lock<std::mutex> lock(_que_lock);
        while (_que.empty() && _running)
        {
            _que_condition.wait(lock);
        }
        if (!_running)
        {
            throw _thread_queue_exception;
        }
        auto ret = _que.front();
        _que.pop();
        return ret;
    }

    void stop()
    {
        std::lock_guard<std::mutex> lock(_que_lock);
        _running = false;
        _que_condition.notify_one();
    }

private:
    std::mutex _que_lock;
    std::condition_variable _que_condition;
    std::queue<T> _que;
    std::atomic_bool _running;
};

#endif // _AUDIO_QUEUE_H
