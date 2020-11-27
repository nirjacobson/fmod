#include "midi_input.h"

MIDIInput* MIDIInput::_instance = nullptr;

PmError MIDIInput::_pmError = pmNoError;
PmDeviceID MIDIInput::_pmDeviceId = 0;
PortMidiStream* MIDIInput::_pmStream = nullptr;

MIDIInput::MIDIInput()
{

}

MIDIInput* MIDIInput::instance()
{
    if (_instance == nullptr) {
        _instance = new MIDIInput;
    }

    return _instance;
}

void MIDIInput::init()
{
    _pmError = Pm_Initialize();
    if (_pmError != pmNoError) {
        std::cerr << "PortMIDI error: " << Pm_GetErrorText(_pmError) << std::endl;
    }

    if (devices().size() > 0) {
        setDevice(0);
    }
}

void MIDIInput::destroy()
{
    _pmError = Pm_Close(_pmStream);
    if (_pmError != pmNoError) {
        std::cerr << "PortMIDI error: " << Pm_GetErrorText(_pmError) << std::endl;
    }

    _pmError = Pm_Terminate();
    if (_pmError != pmNoError) {
        std::cerr << "PortMIDI error: " << Pm_GetErrorText(_pmError) << std::endl;
    }

    delete _instance;
}

std::vector<std::string> MIDIInput::devices() const
{
    std::vector<std::string> inputDevices;

    int totalDevices = Pm_CountDevices();

    for (int i = 0; i < totalDevices; i++) {
        const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
        if (info->input) {
            inputDevices.push_back(info->name);
        }
    }

    return inputDevices;
}

void MIDIInput::setDevice(const int index)
{
    int totalDevices = Pm_CountDevices();
    int inputDevices = 0;

    for (int i = 0; i < totalDevices; i++) {
        const PmDeviceInfo* info = Pm_GetDeviceInfo(i);

        if (info->input && inputDevices == index) {
            const PmDeviceInfo* currentInfo = Pm_GetDeviceInfo(_pmDeviceId);

            if (currentInfo->opened) {
                _pmError = Pm_Close(_pmStream);
                if (_pmError != pmNoError) {
                    std::cerr << "PortMIDI error: " << Pm_GetErrorText(_pmError) << std::endl;
                }
            }

            _pmDeviceId = i;
            _pmError = Pm_OpenInput(&_pmStream,
                                    _pmDeviceId,
                                    nullptr,
                                    128,
                                    nullptr,
                                    nullptr);
            if (_pmError != pmNoError) {
                std::cerr << "PortMIDI error: " << Pm_GetErrorText(_pmError) << std::endl;
            }

            return;
        }

        inputDevices += info->input;
    }
}

std::vector<long> MIDIInput::read() const
{
    std::vector<long> messages;

    PmEvent buffer[128];
    int read = Pm_Read(_pmStream, buffer, 128);

    for (int i = 0; i < read; i++) {
        messages.push_back(buffer[i].message);
    }

    return messages;
}
