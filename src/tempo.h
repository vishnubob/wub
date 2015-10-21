#ifndef _TEMPO_H
#define _TEMPO_H

#define AUBIO_UNSTABLE 1

#include <aubio/aubio.h>
#include <stdio.h>
#include "includes.h"

class Tempo
{
public:
    Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const string &method);
    virtual ~Tempo();
    bool open();
    void close();
    void feed(vecf *buf);
    virtual void tempo_callback(float bpm, float confidence) = 0;

private:
    aubio_tempo_t *_tempo;
    fvec_t *_inbuf;
    fvec_t *_outbuf;
    uint32_t _win_s;
    uint32_t _bin_s;
    uint32_t _sample_rate;
    string _method;
};

#endif // _TEMPO_H
