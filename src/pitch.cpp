#include "pitch.h"

Pitch::Pitch(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _win_s(win_s), _bin_s(bin_s), _sample_rate(sample_rate), _method(method)
{}

Pitch::~Pitch()
{}

void Pitch::thread_loop()
{
    fvec_t *outbuf = new_fvec(_win_s / 4);
    aubio_pitch_t *pitch = new_aubio_pitch((char *)_method.c_str(), _win_s, _bin_s, _sample_rate);

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

        /* execute aubio's pitch detection algorithm */
        aubio_pitch_do(pitch, frame.get(), outbuf);

        /* a beat occured, notify our callback */
        pitch_callback(fvec_get_sample(outbuf, 0));
    }

    del_fvec(outbuf);
    del_aubio_pitch(pitch);
}
