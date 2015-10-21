#ifndef _AUDIO_SOURCE_H
#define _AUDIO_SOURCE_H

#include "includes.h"

class AudioSource
{
public:
    virtual ~AudioSource() = 0;
    virtual bool open() = 0;
    virtual vecf* capture() = 0;
    virtual void close() = 0;
};

#endif // _AUDIO_SOURCE_H
