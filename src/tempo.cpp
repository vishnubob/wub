#include "tempo.h"

Tempo::Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const string &method) :
    _win_s(win_s), _bin_s(bin_s), _sample_rate(sample_rate), _method(method)
{}

Tempo::~Tempo()
{}

bool Tempo::open()
{
    _inbuf = new_fvec(_win_s);
    _outbuf = new_fvec(_win_s / 4);
    _tempo = new_aubio_tempo((char *)_method.c_str(), _win_s, _bin_s, _sample_rate);
    return true;
}

void Tempo::feed(vecf *buf)
{
    smpl_t bpm, confidence;
    _inbuf->data = (smpl_t*) &buf->front();
    vecf::iterator it = buf->begin();
    for (int idx = 0; idx < buf->size(); ++idx)
    {
        fvec_set_sample(_inbuf, it[idx], idx);
    }
    aubio_tempo_do(_tempo, _inbuf, _outbuf);
    bpm = aubio_tempo_get_bpm(_tempo);
    confidence = aubio_tempo_get_confidence(_tempo);
    if (fvec_get_sample(_outbuf, 0))
    {
        tempo_callback(bpm, confidence);
    }
}

void Tempo::close()
{
    del_aubio_tempo(_tempo);
    del_fvec(_inbuf);
    del_fvec(_outbuf);
    aubio_cleanup();
}
