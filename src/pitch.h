#ifndef _PITCH_H
#define _PITCH_H

#include "aubio_module.h"

class Pitch : public AubioModule
{
public:
    Pitch(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method);
    virtual ~Pitch();
    void thread_loop();
    virtual void pitch_callback(float pitch) = 0;

private:
    uint32_t _win_s;
    uint32_t _bin_s;
    uint32_t _sample_rate;
    std::string _method;
};

#endif // _PITCH_H
