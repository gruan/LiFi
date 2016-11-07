#include <iostream>
#include "FourByteFiveByteEncoder.h"

FourByteFiveByteEncoder::FourByteFiveByteEncoder()
{
    m_table = new map<string, string>();

    // Encoding based on http://www.erg.abdn.ac.uk/Users/gorry/course/phy-pages/4b5b.html
    m_table->insert(pair<string,string>("0000", "11110"));
    m_table->insert(pair<string,string>("0001", "01001"));
    m_table->insert(pair<string,string>("0010", "10100"));
    m_table->insert(pair<string,string>("0011", "10101"));
    m_table->insert(pair<string,string>("0100", "01010"));
    m_table->insert(pair<string,string>("0101", "01011"));
    m_table->insert(pair<string,string>("0110", "01110"));
    m_table->insert(pair<string,string>("0111", "01111"));
    m_table->insert(pair<string,string>("1000", "10010"));
    m_table->insert(pair<string,string>("1001", "10011"));
    m_table->insert(pair<string,string>("1010", "10110"));
    m_table->insert(pair<string,string>("1011", "10111"));
    m_table->insert(pair<string,string>("1100", "11010"));
    m_table->insert(pair<string,string>("1101", "11011"));
    m_table->insert(pair<string,string>("1110", "11100"));
    m_table->insert(pair<string,string>("1111", "11101"));
}

const string & FourByteFiveByteEncoder::encode(const string & str) const
{
    cout << str << endl;
    return m_table->at(str);
}

size_t FourByteFiveByteEncoder::numBitsAfterEncoding(size_t numBits) const
{
    return numBits * 5 / 4;
}

FourByteFiveByteEncoder::~FourByteFiveByteEncoder()
{
    m_table->clear();
    delete m_table;
}
