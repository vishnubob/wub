#ifndef _ONSET_H
#define _ONSET_H

#include "aubio_module.h"

class Onset : public AubioModule
{
public:
    Onset(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method);
    virtual ~Onset();
    void process_frame(_fvec_ptr frame);
    virtual void onset_callback(smpl_t ms, smpl_t last_s, uint32_t frame) = 0;

    smpl_t get_silence() { return aubio_onset_get_silence(_onset); }
    void set_silence(smpl_t silence) { aubio_onset_set_silence(_onset, silence); }

private:
    uint32_t _buf_s;
    uint32_t _hop_s;
    uint32_t _sample_rate;
    std::string _method;
    fvec_t *_outbuf;
    aubio_onset_t *_onset;
};

#endif // _ONSET_H
