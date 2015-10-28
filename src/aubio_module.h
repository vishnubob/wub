#ifndef _AUBIO_MODULE_H
#define _AUBIO_MODULE_H

#include <thread>
#include <atomic>
#include <stdio.h>
#include "includes.h"
#include "audio_source.h"

class AubioModule
{
public:
    AubioModule();
    virtual ~AubioModule();
    bool bind(AudioSource &source);
    void thread_loop();
    virtual void process_frame(_fvec_ptr frame) = 0;

    size_t get_last_frame() { return _last_frame; }

protected:
    std::thread _thread;
    _fvec_ptr_que _que;
    std::atomic_bool _running;
    size_t _last_frame;
    size_t _current_frame;
};

#endif // _AUBIO_MODULE_H
