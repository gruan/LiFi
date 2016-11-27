#ifndef SYMBOL_ENCODE_H
#define SYMBOL_ENCODE_H

#pragma once

class SymbolEncode
{
public:
    static void charToBitstring(char c, char * buf);
    static void bitstringToChar(char * buf, char & c);
};

#endif
