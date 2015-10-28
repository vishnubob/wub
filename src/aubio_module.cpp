#include "aubio_module.h"

AubioModule::AubioModule() :
    _running(false), _last_frame(0)
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

void AubioModule::thread_loop()
{
    while (_running)
    {
        _fvec_ptr frame;
        try
        {
            frame = _que.dequeue();
            _current_frame += 1;
        } catch (ThreadQueueException &exc)
        {
            _running = false;
            break;
        }
        process_frame(frame);
    }
}
