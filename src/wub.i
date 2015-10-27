%module(directors="1") wub

%include <stdint.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_shared_ptr.i>
%include <carrays.i>

%{
#include "aubio_module.h"
#include "fft.h"
#include "tempo.h"
#include "onset.h"
#include "pitch.h"
#include "audio_source.h"
#include "alsa_audio_source.h"
%}

%typemap(directorin) cvec_t*
{
    PyObject *_list = PyList_New($1->length);
    for (size_t idx = 0; idx < $1->length; ++idx) 
    {
        PyObject *item = Py_BuildValue("(ff)", $1->norm[idx], $1->phas[idx]);
        PyList_SetItem(_list, idx, item);
    }
    $input = _list;
}

%include "audio_source.h"
%include "alsa_audio_source.h"
%include "alsa_audio_source.h"

%include "aubio_module.h"

/* Tempo */
%feature("director") Tempo;
%feature("nodirector") Tempo::thread_loop;
%feature("nodirector") Tempo::bind;
%include "tempo.h"

/* FFT */
%feature("director") FFT;
%feature("nodirector") FFT::thread_loop;
%feature("nodirector") FFT::bind;
%include "fft.h"

/* Onset */
%feature("director") Onset;
%feature("nodirector") Onset::thread_loop;
%feature("nodirector") Onset::bind;
%include "onset.h"

/* Pitch */
%feature("director") Pitch;
%feature("nodirector") Pitch::thread_loop;
%feature("nodirector") Pitch::bind;
%include "pitch.h"
