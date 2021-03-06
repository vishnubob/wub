#include "audio_source.h"

template class ThreadQueue<std::shared_ptr<fvec_t> >;

bool AudioSource::start()
{
    if (!_running)
    {
        _running = true;
        _thread = std::move(std::thread(&AudioSource::thread_loop, this));
    }
    return _running;
}

void AudioSource::stop() 
{
    if (!_running) return;
    _running = false;
    _thread.join();
}

void AudioSource::register_queue(_fvec_ptr_que *que)
{
    if (_running) return;
    _queue_list.push_back(que);
}

void AudioSource::thread_loop()
{
    if (!_running) return;
    while (_running)
    {
        vecf* raw_frame = capture();
        _fvec_ptr aubio_frame(new_fvec(raw_frame->size()), [](fvec_t* ptr){ del_fvec(ptr); } );
        vecf::iterator it = std::begin(*raw_frame);

        /* copy vector of floats to the aubio frame */
        for (size_t idx = 0; idx < raw_frame->size(); idx += _channels)
        {
            smpl_t value = 0;
            for (size_t ch = 0; ch < _channels; ++ch) 
            {
                value += it[idx + ch];
            }
            value /= (smpl_t)_channels;
            fvec_set_sample(aubio_frame.get(), value, idx / _channels);
        }

        /* push the new aubio frame into the outgoing queues */
        for (auto listener = std::begin(_queue_list); listener != std::end(_queue_list); ++listener)
        {
            (*listener)->enqueue(aubio_frame);
        }

        /* free the original vector of floats */
        delete raw_frame;
    }
    /* inform client queue's we are finished */
    for (auto listener = std::begin(_queue_list); listener != std::end(_queue_list); ++listener)
    {
        (*listener)->stop();
    }
}
