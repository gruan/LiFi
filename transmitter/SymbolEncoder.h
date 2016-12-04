#ifndef SYMBOL_ENCODER_H
#define SYMBOL_ENCODER_H

#pragma once

class SymbolEncoder
{
public:
    SymbolEncoder();

    static void charToBitstring(char c, char * buf);
    const char * charToBitstring4B5BFirstHalf(char c);
    const char * charToBitstring4B5BSecondHalf(char c);
private:
    const char * m_encodeTable[16];
};

#endif
