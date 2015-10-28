#ifndef _FFT_H
#define _FFT_H

#include "aubio_module.h"

class FFT : public AubioModule
{
public:
    FFT(uint32_t win_s);
    virtual ~FFT();
    void process_frame(_fvec_ptr frame);
    virtual void fft_callback(cvec_t *outbuf) = 0;

private:
    uint32_t _win_s;
    aubio_fft_t *_fft;
    cvec_t *_outbuf;
};

#endif // _FFT_H
