#include "alsa_audio_source.h"

ALSAAudioSource::ALSAAudioSource(uint32_t sample_rate, const std::string& card, uint32_t channels, uint32_t bufsize) :
    AudioSource(), _card(card), _sample_rate(sample_rate), _channels(channels), _bufsize(bufsize), _source_handle(nullptr)
{}

bool ALSAAudioSource::start()
{
    int err;
    snd_pcm_hw_params_t *hw_params;

    if ((err = snd_pcm_open(&_source_handle, _card.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) 
    {
        fprintf(stderr, "cannot open audio device %s (%s)\n", _card.c_str(), snd_strerror(err));
        return false;
    }
       
    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0)
    {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
        return false;
    }
             
    if ((err = snd_pcm_hw_params_any(_source_handle, hw_params)) < 0)
    {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
        return false;
    }

    if ((err = snd_pcm_hw_params_set_access(_source_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        fprintf (stderr, "cannot set access type (%s)\n", snd_strerror(err));
        return false;
    }

    if ((err = snd_pcm_hw_params_set_format(_source_handle, hw_params, SND_PCM_FORMAT_FLOAT_LE)) < 0)
    {
        fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
        return false;
    }

    if ((err = snd_pcm_hw_params_set_rate(_source_handle, hw_params, _sample_rate, 0)) < 0)
    {
        fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
        return false;
    }

    if ((err = snd_pcm_hw_params_set_channels(_source_handle, hw_params, _channels)) < 0)
    {
        fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
        return false;
    }

    if ((err = snd_pcm_hw_params(_source_handle, hw_params)) < 0)
    {
        fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
        return false;
    }

    snd_pcm_hw_params_free(hw_params);

    if ((err = snd_pcm_prepare(_source_handle)) < 0)
    {
        fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
        return false;
    }
    return AudioSource::start();
}

vecf* ALSAAudioSource::capture()
{
    int err;
    vecf *buf = new vecf(_channels * _bufsize);
    void *bufptr = (void*) &(buf->front());
    if ((err = snd_pcm_readi(_source_handle, bufptr, _bufsize)) != (int)_bufsize) 
    {
        fprintf(stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
    }
    return buf;
}

void ALSAAudioSource::stop()
{
    AudioSource::stop();
    if (_source_handle != nullptr)
    {
        snd_pcm_close(_source_handle);
    }
    _source_handle = nullptr;
}
