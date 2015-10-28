#include "tempo.h"

Tempo::Tempo(uint32_t buf_s, uint32_t hop_s, uint32_t sample_rate, const std::string &method) :
    AubioModule(), _buf_s(buf_s), _hop_s(hop_s), _sample_rate(sample_rate), _method(method)
{
    _outbuf = new_fvec(_buf_s / 4);
    _tempo = new_aubio_tempo((char *)_method.c_str(), _buf_s, _hop_s, _sample_rate);
}

Tempo::~Tempo()
{
    del_fvec(_outbuf);
    del_aubio_tempo(_tempo);
}

void Tempo::process_frame(_fvec_ptr frame)
{
    /* execute aubio's tempo detection algorithm */
    aubio_tempo_do(_tempo, frame.get(), _outbuf);

    /* if a beat did not occur, return early */
    if (!fvec_get_sample(_outbuf, 0)) return;

    /* a beat occured, notify our callback */
    _last_frame = _current_frame;
    tempo_callback(aubio_tempo_get_bpm(_tempo), aubio_tempo_get_confidence(_tempo));
}
