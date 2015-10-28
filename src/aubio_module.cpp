#include "aubio_module.h"

AubioModule::AubioModule() :
    _running(false)
{}

AubioModule::~AubioModule()
{}

bool AubioModule::bind(AudioSource &source)
{
    if (!_running)
    {
        source.register_queue(&_que);
        _running = true;
        _thread = std::move(std::thread(&AubioModule::thread_loop, this));
    }
    return _running;
}
