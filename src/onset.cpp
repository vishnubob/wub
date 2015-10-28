#include "onset.h"

Onset::Onset(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _buf_s(buf_s), _hop_s(hop_s), _sample_rate(sample_rate), _method(method)
{
    _outbuf = new_fvec(_buf_s / 4);
    _onset = new_aubio_onset((char *)_method.c_str(), _buf_s, _hop_s, _sample_rate);
}

Onset::~Onset()
{
    del_fvec(_outbuf);
    del_aubio_onset(_onset);
}

void Onset::process_frame(_fvec_ptr frame)
{
    /* execute aubio's onset detection algorithm */
    aubio_onset_do(_onset, frame.get(), _outbuf);

    /* if a beat did not occur, return early */
    if (!fvec_get_sample(_outbuf, 0)) return;
    _last_frame = _current_frame;

    /* an onset occured, notify our callback */
    onset_callback(aubio_onset_get_last_ms(_onset), aubio_onset_get_last_s(_onset), aubio_onset_get_last(_onset));
}
