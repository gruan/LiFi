#define BITS_PER_BYTE 8

#include "SymbolEncode.h"

const int bitmasks[BITS_PER_BYTE] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void SymbolEncode::charToBitstring(char c, char * buf)
{
    for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
        buf[BITS_PER_BYTE - i - 1] = ((c & bitmasks[i]) >> i) + '0';
}

void SymbolEncode::bitstringToChar(char * buf, char & c)
{
    for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
        c |= (buf[BITS_PER_BYTE - i - 1] - '0') << i;
}
