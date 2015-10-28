#include "onset.h"

Onset::Onset(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _win_s(win_s), _bin_s(bin_s), _sample_rate(sample_rate), _method(method)
{}

Onset::~Onset()
{}

void Onset::thread_loop()
{
    fvec_t *outbuf = new_fvec(_win_s / 4);
    aubio_onset_t *onset = new_aubio_onset((char *)_method.c_str(), _win_s, _bin_s, _sample_rate);

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

        /* execute aubio's onset detection algorithm */
        aubio_onset_do(onset, frame.get(), outbuf);

        /* if a beat did not occur, return early */
        if (!fvec_get_sample(outbuf, 0)) continue;

        /* an onset occured, notify our callback */
        onset_callback(aubio_onset_get_last_ms(onset), aubio_onset_get_last_s(onset), aubio_onset_get_last(onset));
    }

    del_fvec(outbuf);
    del_aubio_onset(onset);
}
