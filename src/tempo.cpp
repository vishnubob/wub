#include "tempo.h"

Tempo::Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _win_s(win_s), _bin_s(bin_s), _sample_rate(sample_rate), _method(method)
{}

Tempo::~Tempo()
{}

void Tempo::thread_loop()
{
    fvec_t *outbuf = new_fvec(_win_s / 4);
    aubio_tempo_t *tempo = new_aubio_tempo((char *)_method.c_str(), _win_s, _bin_s, _sample_rate);

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
        aubio_tempo_do(tempo, frame.get(), outbuf);

        /* if a beat did not occur, return early */
        if (!fvec_get_sample(outbuf, 0)) continue;

        /* a beat occured, notify our callback */
        tempo_callback(aubio_tempo_get_bpm(tempo), aubio_tempo_get_confidence(tempo));
    }

    del_fvec(outbuf);
    del_aubio_tempo(tempo);
}
