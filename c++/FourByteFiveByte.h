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
    size_t numBitsAfterEncoding(size_t numBits) const;

private:
    map<string, string> * m_encodeTable;
    map<string, string> * m_decodeTable;
};

#endif
