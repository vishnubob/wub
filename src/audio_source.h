#ifndef _AUDIO_SOURCE_H
#define _AUDIO_SOURCE_H

#include <thread>
#include <atomic>
#include "includes.h"
#include "thread_queue.h"

class AudioSource
{
public:
    AudioSource();
    virtual ~AudioSource();
    virtual vecf* capture() = 0;
    virtual bool start();
    virtual void stop();
    void register_queue(_fvec_ptr_que *que);

protected:
    virtual void thread_loop();

private:
    std::atomic_bool _running;
    std::thread _thread;
    std::vector<_fvec_ptr_que*> _queue_list;
};

#endif // _AUDIO_SOURCE_H
