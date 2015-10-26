#ifndef _TEMPO_H
#define _TEMPO_H

#define AUBIO_UNSTABLE 1

#include <thread>
#include <atomic>
#include <aubio/aubio.h>
#include <stdio.h>
#include "includes.h"
#include "audio_source.h"

class Tempo
{
public:
    Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method);
    virtual ~Tempo();
    bool bind(AudioSource &source);
    void thread_loop();
    virtual void tempo_callback(float bpm, float confidence) = 0;

private:
    aubio_tempo_t *_tempo;
    fvec_t *_outbuf;
    uint32_t _win_s;
    uint32_t _bin_s;
    uint32_t _sample_rate;
    std::string _method;
    std::thread *_thread;
    _fvec_ptr_que _que;
    std::atomic_bool _running;
};

#endif // _TEMPO_H
