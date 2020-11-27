#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include <iostream>
#include <string>
#include <vector>

#include "portmidi.h"

class MIDIInput
{
public:
    MIDIInput();

    static MIDIInput* instance();

    void init();
    void destroy();

    std::vector<std::string> devices() const;

    void setDevice(const int index);

    std::vector<long> read() const;

private:
    static MIDIInput* _instance;

    static PmError _pmError;
    static PmDeviceID _pmDeviceId;
    static PortMidiStream* _pmStream;
};

#endif // MIDIINPUT_H
