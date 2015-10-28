#include "pitch.h"

Pitch::Pitch(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _buf_s(buf_s), _hop_s(hop_s), _sample_rate(sample_rate), _method(method)
{
    _outbuf = new_fvec(_buf_s / 4);
    _pitch = new_aubio_pitch((char *)_method.c_str(), _buf_s, _hop_s, _sample_rate);
}

Pitch::~Pitch()
{
    del_fvec(_outbuf);
    del_aubio_pitch(_pitch);
}

void Pitch::process_frame(_fvec_ptr frame)
{
    /* execute aubio's pitch detection algorithm */
    aubio_pitch_do(_pitch, frame.get(), _outbuf);
    if (fvec_get_sample(_outbuf, 0) == 0.0) return;
    _last_frame = _current_frame;
    pitch_callback(fvec_get_sample(_outbuf, 0), aubio_pitch_get_confidence(_pitch));
}
