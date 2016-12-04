/**
 * Decodes the transmission of ruanEncoding.
 */

#include "TransmissionDecoder.h"

// Returns '!' on error. Otherwise '0' or '1'
char TransmissionDecoder::ruanDecoding(char currBit)
{
    char decodedBit = currBit;
    if (currBit == m_repeat && (m_lastBit == m_off || m_lastBit == m_on))
        decodedBit = m_lastBit;

    if (decodedBit == m_off) {
        m_lastBit = currBit;
        return '0';
    }

    if (decodedBit == m_on) {
        m_lastBit = currBit;
        return '1';
    }

    return '!';
}
