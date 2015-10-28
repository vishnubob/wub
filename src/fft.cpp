#include "fft.h"

FFT::FFT(uint32_t win_s) :
    AubioModule(), _win_s(win_s)
{
    _fft = new_aubio_fft(_win_s);
    _outbuf = new_cvec(_win_s);
}


FFT::~FFT()
{
    del_cvec(_outbuf);
    del_aubio_fft(_fft);
}

void FFT::process_frame(_fvec_ptr frame)
{
    /* execute aubio's tempo detection algorithm */
    aubio_fft_do(_fft, frame.get(), _outbuf);

    /* a beat occured, notify our callback */
    _last_frame = _current_frame;
    fft_callback(_outbuf);
}
