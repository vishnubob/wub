#include "tempo.h"

Tempo::Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method) :
    _win_s(win_s), _bin_s(bin_s), _sample_rate(sample_rate), _method(method)
{}

Tempo::~Tempo()
{}

bool Tempo::bind(AudioSource &source)
{
    if (!_running)
    {
        _outbuf = new_fvec(_win_s / 4);
        _tempo = new_aubio_tempo((char *)_method.c_str(), _win_s, _bin_s, _sample_rate);
        source.register_queue(&_que);
        _running = true;
        _thread = new std::thread(&Tempo::thread_loop, this);
    }
    return _running;
}

void Tempo::thread_loop()
{
    while (_running)
    {
        _fvec_ptr frame;
        try
        {
            frame = _que.dequeue();
        } catch (ThreadQueueException &exc)
        {
            _running = false;
            break;
        }

        /* execute aubio's tempo detection algorithm */
        aubio_tempo_do(_tempo, frame.get(), _outbuf);

        /* if a beat did not occur, return early */
        if (!fvec_get_sample(_outbuf, 0)) continue;

        /* a beat occured, notify our callback */
        tempo_callback(aubio_tempo_get_bpm(_tempo), aubio_tempo_get_confidence(_tempo));
    }
}
