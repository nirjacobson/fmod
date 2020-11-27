#include "midipoller.h"

MIDIPoller::MIDIPoller()
    : _midiInput(MIDIInput::instance())
    , _stop(false)
{

}

MIDIPoller::~MIDIPoller()
{

}

void MIDIPoller::stop()
{
    _stopLock.lock();
    _stop = true;
    _stopLock.unlock();
}

void MIDIPoller::start(Priority p)
{
    _stopLock.lock();
    _stop = false;
    _stopLock.unlock();

    QThread::start(p);
}

void MIDIPoller::run()
{
    while (true) {
        _stopLock.lock();
        bool stop = _stop;
        _stopLock.unlock();
        if (stop) return;

        std::vector<long> messages = _midiInput->read();
        if (!messages.empty()) {
            for (const long message : messages) {
                emit receivedMessage(message);
            }
        }

        QThread::msleep(1);
    }
}
