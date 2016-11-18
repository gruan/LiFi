#include <iostream>
#include "FourByteFiveByte.h"

FourByteFiveByte::FourByteFiveByte()
{
    m_encodeTable = new map<string, string>();

    // Encoding based on http://www.erg.abdn.ac.uk/Users/gorry/course/phy-pages/4b5b.html
    m_encodeTable->insert(pair<string, string>("0000", "11110"));
    m_encodeTable->insert(pair<string, string>("0001", "01001"));
    m_encodeTable->insert(pair<string, string>("0010", "10100"));
    m_encodeTable->insert(pair<string, string>("0011", "10101"));
    m_encodeTable->insert(pair<string, string>("0100", "01010"));
    m_encodeTable->insert(pair<string, string>("0101", "01011"));
    m_encodeTable->insert(pair<string, string>("0110", "01110"));
    m_encodeTable->insert(pair<string, string>("0111", "01111"));
    m_encodeTable->insert(pair<string, string>("1000", "10010"));
    m_encodeTable->insert(pair<string, string>("1001", "10011"));
    m_encodeTable->insert(pair<string, string>("1010", "10110"));
    m_encodeTable->insert(pair<string, string>("1011", "10111"));
    m_encodeTable->insert(pair<string, string>("1100", "11010"));
    m_encodeTable->insert(pair<string, string>("1101", "11011"));
    m_encodeTable->insert(pair<string, string>("1110", "11100"));
    m_encodeTable->insert(pair<string, string>("1111", "11101"));

    m_decodeTable = new map<string, string>();

    // Decoding is inverse of encoding.
    m_decodeTable->insert(pair<string, string>("11110", "0000"));
    m_decodeTable->insert(pair<string, string>("01001", "0001"));
    m_decodeTable->insert(pair<string, string>("10100", "0010"));
    m_decodeTable->insert(pair<string, string>("10101", "0011"));
    m_decodeTable->insert(pair<string, string>("01010", "0100"));
    m_decodeTable->insert(pair<string, string>("01011", "0101"));
    m_decodeTable->insert(pair<string, string>("01110", "0110"));
    m_decodeTable->insert(pair<string, string>("01111", "0111"));
    m_decodeTable->insert(pair<string, string>("10010", "1000"));
    m_decodeTable->insert(pair<string, string>("10011", "1001"));
    m_decodeTable->insert(pair<string, string>("10110", "1010"));
    m_decodeTable->insert(pair<string, string>("10111", "1011"));
    m_decodeTable->insert(pair<string, string>("11010", "1100"));
    m_decodeTable->insert(pair<string, string>("11011", "1101"));
    m_decodeTable->insert(pair<string, string>("11100", "1110"));
    m_decodeTable->insert(pair<string, string>("11101", "1111"));
}

const string & FourByteFiveByte::encode(const string & str) const
{
    cout << str << "\t Bits of character" << endl;
    return m_encodeTable->at(str);
}

const string & FourByteFiveByte::decode(const string & str) const
{
     return m_decodeTable->at(str);
}

size_t FourByteFiveByte::numBitsAfterEncoding(size_t numBits) const
{
    return numBits * 5 / 4;
}

FourByteFiveByte::~FourByteFiveByte()
{
    m_encodeTable->clear();
    delete m_encodeTable;

    m_decodeTable->clear();
    delete m_decodeTable;
}
