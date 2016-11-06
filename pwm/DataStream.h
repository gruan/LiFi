#ifndef DATASTREAM_H
#define DATASTREAM_H

#pragma once

#include <sstream>

using namespace std;

class DataStream
{
public:
    DataStream(size_t, char *);
    ~DataStream();

    int next(char * buf);
    bool isEmpty();
private:
    int addToStream(char);
    int charToSize(char, size_t & res);
    void numToBinary(size_t num, string & binaryRep);

    size_t m_bitsOfChar;
    stringstream * m_stream;
};

#endif
