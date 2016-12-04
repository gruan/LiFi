#define BITS_PER_BYTE 8

#include "SymbolDecoder.h"

void SymbolDecoder::bitstringToChar(char * buf, char & c)
{
    for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
        c |= (buf[BITS_PER_BYTE - i - 1] - '0') << i;
}

char SymbolDecoder::decodeNextBit(char bit)
{
    m_queue.enqueue(bit);

    if (m_queue.count() == BITS_PER_BYTE) {
        char asciiChar = '\0';
        for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
            asciiChar |= (m_queue.dequeue() - '0') << i;
        return asciiChar;
    }

    return -1;
}
