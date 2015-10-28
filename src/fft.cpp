#include "fft.h"

FFT::FFT(uint32_t win_s) :
    AubioModule(), _win_s(win_s)
{}

FFT::~FFT()
{}

void FFT::thread_loop()
{
    aubio_fft_t *fft = new_aubio_fft(_win_s);
    cvec_t *outbuf = new_cvec(_win_s);

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
        aubio_fft_do(fft, frame.get(), outbuf);

        /* a beat occured, notify our callback */
        fft_callback(outbuf);
    }

    del_cvec(outbuf);
    del_aubio_fft(fft);
}
