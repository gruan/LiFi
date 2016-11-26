#include <fstream>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ArduinoSerial.h"
#include "DataStream.h"

using namespace std;

const string USAGE_STR = "Usage: fileToBits filepath\n";

const size_t BAUD_RATE = 9600;
const char * SERIAL_PORT = "/dev/cu.usbmodem1411";
const size_t ASCII_NUM_BITS = 8;

void validateCLIArguments(int argc, char * argv[])
{
    if (argc != 2) {
        cout << USAGE_STR << endl;
        exit(EXIT_FAILURE);
    }
}

int openSerialPort()
{
    int fd = serialport_init(SERIAL_PORT, BAUD_RATE);
    if (fd == -1) {
        fprintf(stderr, "[ERR] Couldn't open port\n");
        exit(EXIT_FAILURE);
    }
    serialport_flush(fd);

    return fd;
}

int main (int argc, char * argv[]) {
    validateCLIArguments(argc, argv);

    char * filePath = argv[1];
    bool isEncoderEnabled = true;

    DataStream * stream = new DataStream(ASCII_NUM_BITS, filePath, isEncoderEnabled);
    size_t bufLen = stream->bufSizeNeeded();
    char * buf = new char[bufLen];
    memset(buf, 0, bufLen);

    cout << "Opening Serial Port" << endl;

    int arduinofd = openSerialPort();

    while(stream->next(buf) == 0) {
        cout << buf << "\tBitstring sent" << endl;
        serialport_write(arduinofd, buf);
    }

    serialport_close(arduinofd);
    delete stream;

    exit(EXIT_SUCCESS);
}
