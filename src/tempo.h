#ifndef _TEMPO_H
#define _TEMPO_H

#include "aubio_module.h"

class Tempo : public AubioModule
{
public:
    Tempo(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method);
    virtual ~Tempo();
    void process_frame(_fvec_ptr frame);
    virtual void tempo_callback(smpl_t bpm, smpl_t confidence) = 0;

    smpl_t get_silence() { return aubio_tempo_get_silence(_tempo); }
    void set_silence(smpl_t silence) { aubio_tempo_set_silence(_tempo, silence); }

private:
    uint32_t _buf_s;
    uint32_t _hop_s;
    uint32_t _sample_rate;
    std::string _method;
    fvec_t *_outbuf;
    aubio_tempo_t *_tempo;
};

#endif // _TEMPO_H
