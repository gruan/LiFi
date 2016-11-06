#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * USAGE_STR = "Usage: fileToBits filepath\n";

size_t BUFFER_SIZE = 50;
size_t SIZE_OF_CHAR = 8;

void validateCLIArguments(int argc, char * argv[])
{
    if (argc != 2) {
        printf("%s", USAGE_STR);
        exit(EXIT_FAILURE);
    }
}

// Assumes ASCII. Specifically, assumes the size of a character is represented
// using 8 bits.
// Caller is respnsible for freeing returned string.
char * decimalToBinary(size_t n)
{
    char * binStr = (char *) malloc(SIZE_OF_CHAR * sizeof(char) + 1);
    memset((void *) binStr, (int) '0', SIZE_OF_CHAR * sizeof(char));
    binStr[SIZE_OF_CHAR] = '\0';

    int strIndex = SIZE_OF_CHAR - 1;

    while (n != 0 && strIndex >= 0) {
        binStr[strIndex--] = n % 2 ? '1' : '0';
        n /= 2;
    }

    return binStr;
}

void printBinaryOfChar(char c)
{
    int charCode = (int) c;
    if (charCode < 0) {
        printf("FAILURE: char %c has value %d\n", c, charCode);
        exit(EXIT_FAILURE);
    }
    char * binOfChar = decimalToBinary((size_t) charCode);

    printf("%s", binOfChar);

    if (binOfChar)
        free(binOfChar);
}

int main (int argc, char * argv[]) {
    validateCLIArguments(argc, argv);

    char * filePath = argv[1];

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filePath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ( (read = getline(&line, &len, fp)) != -1 ) {
        size_t lineLen = strlen(line);
        for (size_t i = 0; i < lineLen; ++i) {
            printBinaryOfChar(line[i]);

        }
    }

    fclose(fp);
    if (line)
        free(line);

    exit(EXIT_SUCCESS);
}
