#ifndef _ONSET_H
#define _ONSET_H

#include "aubio_module.h"

class Onset : public AubioModule
{
public:
    Onset(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const std::string &method);
    virtual ~Onset();
    void thread_loop();
    virtual void onset_callback(float ms, float last_s, uint32_t frame) = 0;

private:
    uint32_t _win_s;
    uint32_t _bin_s;
    uint32_t _sample_rate;
    std::string _method;
};

#endif // _ONSET_H
