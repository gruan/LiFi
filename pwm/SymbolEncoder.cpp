#define BITS_PER_BYTE 8

#include "SymbolEncoder.h"

const int bitmasks[BITS_PER_BYTE] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void SymbolEncoder::charToBitstring(char c, char * buf)
{
    for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
        buf[BITS_PER_BYTE - i - 1] = ((c & bitmasks[i]) >> i) + '0';
}
