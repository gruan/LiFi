#ifndef TRANSMISSION_DECODER_H
#define TRANSMISSION_DECODER_H

#pragma once

class TransmissionDecoder
{
public:
    TransmissionDecoder(char off, char repeat, char on)
        : m_lastBit('!'),
          m_off(off),
          m_repeat(repeat),
          m_on(on)
    {}
    char ruanDecoding(char currBit);
private:
    char m_lastBit;
    char m_off;
    char m_repeat;
    char m_on;
};

#endif
