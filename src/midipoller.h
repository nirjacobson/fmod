#ifndef MIDIPOLLER_H
#define MIDIPOLLER_H

#include <QThread>
#include <QMutex>

#include "midi_input.h"

class MIDIPoller : public QThread
{
    Q_OBJECT

signals:
    void receivedMessage(const long msg);

public:
    MIDIPoller();
    ~MIDIPoller();

    void stop();

public slots:
    void start(Priority p = InheritPriority);

    // QThread interface
protected:
    void run();

private:
    MIDIInput* _midiInput;

    QMutex _stopLock;
    bool _stop;
};

#endif // MIDIPOLLER_H
