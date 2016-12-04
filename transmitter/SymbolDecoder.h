#ifndef SYMBOL_DECODER_H
#define SYMBOL_DECODER_H

#pragma once

#include <QueueArray.h>

class SymbolDecoder
{
public:
    static void bitstringToChar(char * buf, char & c);

    // Returns -1
    char decodeNextBit(char bit);

private:
    QueueArray<char> m_queue;
};

#endif
