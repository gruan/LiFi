#define BITS_PER_BYTE 8

#include "SymbolEncoder.h"

const int bitmasks[BITS_PER_BYTE] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

SymbolEncoder::SymbolEncoder()
{
  // 4b5b Encoder. Based on http://www.erg.abdn.ac.uk/Users/gorry/course/phy-pages/4b5b.html
  for (int i = 0; i < 16; ++i) 
    m_encodeTable[i] = "!";
   
  m_encodeTable[0] = "11110";
  m_encodeTable[1] = "01001";
  m_encodeTable[2] = "10100";
  m_encodeTable[3] = "10101";
  m_encodeTable[4] = "01010";
  m_encodeTable[5] = "01011";
  m_encodeTable[6] = "01110";
  m_encodeTable[7] = "01111";
  m_encodeTable[8] = "10010";
  m_encodeTable[9] = "10011";
  m_encodeTable[10] = "10110";
  m_encodeTable[11] = "10111";
  m_encodeTable[12] = "11010";
  m_encodeTable[13] = "11011";
  m_encodeTable[14] = "11100";
  m_encodeTable[15] = "11101";
}

const char * SymbolEncoder::charToBitstring4B5BFirstHalf(char c)
{
  return m_encodeTable[(c >> 4) & 0x0F];
}

const char * SymbolEncoder::charToBitstring4B5BSecondHalf(char c)
{
  return m_encodeTable[c & 0x0F];
}

void SymbolEncoder::charToBitstring(char c, char * buf)
{
    for (int i = BITS_PER_BYTE - 1; i >= 0; --i)
        buf[BITS_PER_BYTE - i - 1] = ((c & bitmasks[i]) >> i) + '0';
}



