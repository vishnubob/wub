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
    virtual ~AubioModule() = 0;
    bool bind(AudioSource &source);
    virtual void thread_loop() = 0;

protected:
    std::thread *_thread;
    _fvec_ptr_que _que;
    std::atomic_bool _running;
};

#endif // _AUBIO_MODULE_H
