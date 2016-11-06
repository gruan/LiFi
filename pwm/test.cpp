#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "DataStream.h"

using namespace std;

string USAGE_STR = "Usage: fileToBits filepath\n";

size_t BUFFER_SIZE = 50;
size_t SIZE_OF_CHAR = 8;

void validateCLIArguments(int argc, char * argv[])
{
    if (argc != 2) {
        cout << USAGE_STR << endl;
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char * argv[]) {
    validateCLIArguments(argc, argv);

    char * filePath = argv[1];

    DataStream * stream = new DataStream(8, filePath);

    char * buf = new char[9];
    memset(buf, 0, 9);
    for (int i = 0; i < 5; ++i) {
        stream->next(buf);
        cout << buf << endl;
    }

    delete stream;

    exit(EXIT_SUCCESS);
}
