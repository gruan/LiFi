#ifndef FOUR_BYTE_FIVE_BYTE_ENCODER_H
#define FOUR_BYTE_FIVE_BYTE_ENCODER_H

#pragma once

#include <map>
#include <string>

using namespace std;

class FourByteFiveByteEncoder {
public:
    FourByteFiveByteEncoder();
    ~FourByteFiveByteEncoder();

    const string & encode(const string &) const;
    size_t numBitsAfterEncoding(size_t numBits) const;

private:
    map<string, string> * m_table;
};

#endif
