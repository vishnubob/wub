#ifndef _TEMPO_H
#define _TEMPO_H

#include "aubio_module.h"

class Tempo : public AubioModule
{
public:
    Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method);
    virtual ~Tempo();
    void thread_loop();
    virtual void tempo_callback(float bpm, float confidence) = 0;

private:
    uint32_t _win_s;
    uint32_t _bin_s;
    uint32_t _sample_rate;
    std::string _method;
};

#endif // _TEMPO_H
