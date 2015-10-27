#ifndef _FFT_H
#define _FFT_H

#include "aubio_module.h"

class FFT : public AubioModule
{
public:
    FFT(uint32_t win_s);
    virtual ~FFT();
    void thread_loop();
    virtual void fft_callback(cvec_t *outbuf) = 0;

private:
    uint32_t _win_s;
};

#endif // _FFT_H
