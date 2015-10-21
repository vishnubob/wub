%module(directors="1") wub

using namespace std;

%include "stdint.i"
%include "std_string.i"
%include "std_vector.i"

%{
#include "tempo.h"
#include "audio_source.h"
#include "alsa_audio_source.h"
#include "includes.h"
#include "wub.h"

class SafeTempo: public Tempo
{
public:
    SafeTempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const string &method) :
        Tempo(win_s, bin_s, sample_rate, method) {}

    virtual ~SafeTempo() {}
    
    virtual void tempo_callback(float bpm, float confidence)
    {
        _gil_state = PyGILState_Ensure();
        tempo(bpm, confidence);
        PyGILState_Release(_gil_state);
    }

    virtual void tempo(float bpm, float confidence) = 0;

private:
    PyGILState_STATE _gil_state;
};
%}

class Tempo 
{
public:
    Tempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const string &method);
    virtual ~Tempo();
    bool open();
    void close();
    virtual void tempo_callback(float bpm, float confidence) = 0;
};

%feature("director") SafeTempo;
class SafeTempo: public Tempo
{
public:
    SafeTempo(uint32_t win_s, uint32_t bin_s, uint32_t sample_rate, const string &method);
    virtual ~SafeTempo();
    bool open();
    void close();
    virtual void tempo_callback(float bpm, float confidence);
    virtual void tempo(float bpm, float confidence) = 0;
};

class AudioSource
{
    virtual bool open() = 0;
    virtual void close() = 0;
};

class ALSAAudioSource : public AudioSource
{
public:
    ALSAAudioSource(uint32_t sample_rate, const string& card, uint32_t channels=2, uint32_t bufsize = 128);
    bool open();
    void close();
};

void start(AudioSource *audio_source, Tempo *tempo);
void stop();
