#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "DataStream.h"

DataStream::DataStream(size_t bitsOfChar, char * filePath)
{
    m_bitsOfChar = bitsOfChar;
    m_stream = new stringstream();
    m_encoder = new FourByteFiveByte();

    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filePath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ( (read = getline(&line, &len, fp)) != -1 ) {
        // Disregard trailing \n added by getline.
        size_t lineLen = strlen(line) - 1;
        for (size_t i = 0; i < lineLen; ++i) {
            // Add character to stream.
            if (addToStream(line[i])) {
                fprintf(stderr, "[ERR] DataStream::DataStream - Could not add %c to stream\n", line[i]);
            }
        }
    }

    fclose(fp);
    if (line)
        free(line);
}

DataStream::~DataStream()
{
    // Clear contents of stringstream.
    m_stream->str(string());
    delete m_stream;
    delete m_encoder;
}

// buf needs to be able to hold m_bitsOfChar.
int DataStream::next(char * buf)
{
    if (m_stream->eof()) {
         fprintf(stdout, "[WARN] DataStream::next - Stream is empty\n");
         return 1;
    }

    if (m_stream->fail()) {
        fprintf(stderr, "[ERR] DataStream::next - Stream failed...");
        return -1;
    }

    m_stream->get(buf, m_encoder->numBitsAfterEncoding(m_bitsOfChar) + 1);
    return 0;
}

int DataStream::charToSize(char c, size_t & res)
{
    int charCode = (int) c;
    if (charCode < 0) {
        fprintf(stderr, "[ERR] DataStream::charToSize - char %c has value %d\n", c, charCode);
        return -1;
    }

    res = (size_t) charCode;
    return 0;
}

void DataStream::numToBinary(size_t num, string & binaryRep)
{
    binaryRep = string(m_bitsOfChar, '0');
    size_t endOfStrIndex = m_bitsOfChar - 1;
    size_t strIndex = 0;

    while (num != 0 && strIndex < m_bitsOfChar) {
        binaryRep[endOfStrIndex - strIndex++] = num % 2 ? '1' : '0';
        num /= 2;
    }
}

int DataStream::addToStream(char c)
{
    size_t charCode;
    if (charToSize(c, charCode)) {
        fprintf(stderr, "[ERR] DataStream::addToStream - char %c could not be converted to unsigned\n", c);
        return -1;
    }

    string binaryRep;
    numToBinary(charCode, binaryRep);

    // Convert with 4B5B
    string firstHalf = binaryRep.substr(0, m_bitsOfChar / 2);
    string secondHalf = binaryRep.substr(m_bitsOfChar / 2 , m_bitsOfChar / 2);

    // printf("Adding character %c with charCode %zu and binary representation %s\n", c, charCode, binaryRep.c_str());

    (*m_stream) << m_encoder->encode(firstHalf);
    (*m_stream) << m_encoder->encode(secondHalf);

    return 0;
}
