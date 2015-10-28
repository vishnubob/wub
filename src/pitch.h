#ifndef _PITCH_H
#define _PITCH_H

#include "aubio_module.h"

class Pitch : public AubioModule
{
public:
    Pitch(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method);
    virtual ~Pitch();
    void process_frame(_fvec_ptr frame);
    virtual void pitch_callback(smpl_t pitch, smpl_t confidence) = 0;

    bool set_unit(const std::string &unit) { return (aubio_pitch_set_unit(_pitch, (char*) unit.c_str()) == 0); }
    bool set_tolerance(smpl_t tolerance) { return (aubio_pitch_set_tolerance(_pitch, tolerance) == 0); }
    smpl_t get_silence() { return aubio_pitch_get_silence(_pitch); }
    void set_silence(smpl_t silence) { aubio_pitch_set_silence(_pitch, silence); }

private:
    uint32_t _buf_s;
    uint32_t _hop_s;
    uint32_t _sample_rate;
    std::string _method;
    fvec_t *_outbuf;
    aubio_pitch_t *_pitch;
};

#endif // _PITCH_H
