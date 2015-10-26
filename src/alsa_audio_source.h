#ifndef _ALSA_AUDIO_SOURCE_H
#define _ALSA_AUDIO_SOURCE_H

#include <alsa/asoundlib.h>
#include "audio_source.h"

class ALSAAudioSource : public AudioSource
{
public:
    ALSAAudioSource(uint32_t sample_rate, const std::string& card, uint32_t channels=2, uint32_t bufsize = 128);
    vecf* capture();
    bool start();
    void stop();

private:
    const std::string _card;
    uint32_t _sample_rate;
    uint32_t _channels;
    uint32_t _bufsize;
    snd_pcm_t *_source_handle;
};

#endif // _ALSA_AUDIO_SOURCE_H
