#ifndef _WUB_H
#define _WUB_H

#include "includes.h"
#include "audio_source.h"
#include "tempo.h"
#include <pthread.h>

void start(AudioSource *audio_source, Tempo *tempo);
void stop();

#endif
