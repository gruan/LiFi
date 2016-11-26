#ifndef FOUR_BYTE_FIVE_BYTE_H
#define FOUR_BYTE_FIVE_BYTE_H

#pragma once

#include <map>
#include <string>

using namespace std;

class FourByteFiveByte {
public:
    FourByteFiveByte();
    ~FourByteFiveByte();

    const string & encode(const string &) const;
    const string & decode(const string &) const;
    static size_t numBitsAfterEncoding(size_t numBits);

private:
    map<string, string> * m_encodeTable;
    map<string, string> * m_decodeTable;
};

#endif
