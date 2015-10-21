#include "wub.h"

static Tempo *_tempo;
static AudioSource *_source;
static pthread_t thread;
static volatile bool _running;

void *run(void *threadid)
{
    while (_running)
    {
        vecf *buf = _source->capture();
        _tempo->feed(buf);
        delete buf;
    }
    pthread_exit(NULL);
}

void start(AudioSource *audio_source, Tempo *tempo)
{
    _tempo = tempo;
    _source = audio_source;
    _running = true;
    pthread_create(&thread, NULL, run, NULL);
}

void stop()
{
    _running = false;
}
