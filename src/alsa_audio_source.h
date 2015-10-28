#ifndef _ALSA_AUDIO_SOURCE_H
#define _ALSA_AUDIO_SOURCE_H

#include <alsa/asoundlib.h>
#include "audio_source.h"

class ALSAAudioSource : public AudioSource
{
public:
    ALSAAudioSource(const std::string& card, uint32_t sample_rate, uint32_t channels=2, uint32_t bufsize = 128) :
        AudioSource(sample_rate, channels, bufsize), _card(card), _source_handle(nullptr)
    {}

    vecf* capture();
    bool start();
    void stop();

    const std::string& get_card() { return _card; }

private:
    const std::string _card;
    snd_pcm_t *_source_handle;
};

#endif // _ALSA_AUDIO_SOURCE_H
