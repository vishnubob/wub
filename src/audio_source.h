#ifndef _AUDIO_SOURCE_H
#define _AUDIO_SOURCE_H

#include <thread>
#include <atomic>
#include "includes.h"
#include "thread_queue.h"

class AudioSource
{
public:
    AudioSource() :
        _running(false), _thread(nullptr) 
        {}

    virtual ~AudioSource();
    virtual vecf* capture() = 0;
    virtual bool start();
    virtual void stop();
    void register_queue(_fvec_ptr_que *que);

protected:
    virtual void thread_loop();

private:
    std::vector<_fvec_ptr_que*> _queue_list;
    std::thread *_thread;
    std::atomic_bool _running;
};

#endif // _AUDIO_SOURCE_H
