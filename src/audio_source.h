#ifndef _AUDIO_SOURCE_H
#define _AUDIO_SOURCE_H

#include <thread>
#include <atomic>
#include "includes.h"
#include "thread_queue.h"

class AudioSource
{
public:
    AudioSource(uint32_t sample_rate, uint32_t channels=2, uint32_t bufsize = 128)
        : _sample_rate(sample_rate), _channels(channels), _bufsize(bufsize), _running(false)
    {}

    virtual ~AudioSource() { stop(); };
    virtual vecf* capture() = 0;
    virtual bool start();
    virtual void stop();
    void register_queue(_fvec_ptr_que *que);

    const uint32_t get_sample_rate() { return _sample_rate; }
    const uint32_t get_buffer_size() { return _bufsize; }
    const uint32_t get_channels() { return _channels; }

protected:
    virtual void thread_loop();

protected:
    uint32_t _sample_rate;
    uint32_t _channels;
    uint32_t _bufsize;
    std::atomic_bool _running;
    std::thread _thread;
    std::vector<_fvec_ptr_que*> _queue_list;
};

#endif // _AUDIO_SOURCE_H
