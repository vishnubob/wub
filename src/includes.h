#ifndef _INCLUDES_H
#define _INCLUDES_H

#define AUBIO_UNSTABLE 1

#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <aubio/aubio.h>
#include "thread_queue.h"

typedef std::vector<smpl_t> vecf;
typedef std::shared_ptr<fvec_t> _fvec_ptr;
typedef ThreadQueue<_fvec_ptr> _fvec_ptr_que;

#endif // _INCLUDES_H
