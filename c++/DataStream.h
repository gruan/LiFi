#ifndef DATASTREAM_H
#define DATASTREAM_H

#pragma once

#include <sstream>
#include "FourByteFiveByte.h"

using namespace std;

class DataStream
{
public:
    DataStream(size_t, char *, bool);
    ~DataStream();

    int next(char * buf);

    size_t bufSizeNeeded();
private:
    int addToStream(char);
    int charToSize(char, size_t & res);
    void numToBinary(size_t num, string & binaryRep);

    size_t m_bitsOfChar;
    stringstream * m_stream;
    FourByteFiveByte * m_encoder;
};

#endif
