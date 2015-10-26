%module(directors="1") wub

%include "stdint.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"

%{
#include "tempo.h"
#include "audio_source.h"
#include "alsa_audio_source.h"
%}

%feature("director") Tempo;
%include "tempo.h"
%include "audio_source.h"
%include "alsa_audio_source.h"

/*
%template(vecf) std::vector<float>;
%template(_vec_ptr) std::shared_ptr<fvec_t>;
%template(_fvec_ptr) ThreadQueue<_fvec_ptr>;
*/

