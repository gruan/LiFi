#ifndef TRANSMISSION_ENCODER_H
#define TRANSMISSION_ENCODER_H

#pragma once

class TransmissionEncoder
{
public:
    TransmissionEncoder(int on, int repeat, int off, int err, int noPower, char specialChar)
        : m_brightnessOn(on),
          m_brightnessRepeat(repeat),
          m_brightnessOff(off),
          m_errBrightness(err),
          m_noPowerBrightness(noPower),
          m_specialChar(specialChar),
          m_repBrightnessFlag(true)
    {}

    int noEncoding(char bit) const;
    int nrziEncoding(char currBit, char lastBit) const;
    int ruanEncoding(char currBit, char lastBit);
private:
    int m_brightnessOn;
    int m_brightnessRepeat;
    int m_brightnessOff;
    int m_errBrightness;
    int m_noPowerBrightness;

    // Special character that indicates that no data has yet been read.
    int m_specialChar;

    // Determines whether the next repetition of the same character should trigger the
    // repetition brightness.
    bool m_repBrightnessFlag;
};

#endif
