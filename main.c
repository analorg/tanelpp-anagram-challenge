#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#define CHUNK 65535
#define CP_LEN 256

struct timeval stop, start;
FILE *file;
size_t bytesRead;

double timeDiff(struct timeval x, struct timeval y)
{
    double xMs, yMs;
    xMs = (double) x.tv_sec * 1000000 + (double) x.tv_usec;
    yMs = (double) y.tv_sec * 1000000 + (double) y.tv_usec;

    return yMs - xMs;
}

int main(int argc, char **argv)
{
    gettimeofday(&start, NULL);
    if (argc < 3) {
        printf("Usage: anagram dictionary-path word(s)\n");
        return argc == 1 ? 0 : 1;
    }
    file = fopen(argv[1], "rb");
    if (!file) {
        printf("Could not open the dictionary file.\n");
        return 1;
    }
    int i = 0, j = 0;
    int actual[CP_LEN] = {0}, expected[CP_LEN] = {0};
    int expectedLength = 0, modifier = 0, currentLength = 0;
    int skip = 0, same = 1;
    unsigned char *word, *wordIterator;
    if (argc > 3) {
        word = malloc(CHUNK);
        wordIterator = word;
        for (i = 2; i < argc; i++) {
            if (wordIterator != word) {
                (*wordIterator++) = ' ';
            }
            for (j = 0; argv[i][j]; j++) {
                (*wordIterator++) = (unsigned char) argv[i][j];
            }
        }
        *wordIterator = '\0';
    } else {
        word = (unsigned char*) argv[2];
    }
    unsigned char buf[CHUNK];
    for (i = 0; word[i]; i++) {
        expected[word[i]]++;
        expectedLength++;
    }
    unsigned char current[expectedLength];
    unsigned char csv[CHUNK];
    unsigned char *csvIterator = csv;
    while ((bytesRead = fread(buf, 1, sizeof buf, file)) > 0) {
        for (i = 0; i < bytesRead; i++) {
            if (buf[i] == '\n') {
                if (!skip && !same && currentLength == expectedLength) {
                    (*csvIterator++) = ',';
                    for (j = 0; j < currentLength; j++) {
                        (*csvIterator++) = current[j];
                    }
                }
                modifier += expectedLength;
                currentLength = 0;
                skip = 0;
                same = 1;
                continue;
            }
            if (skip || buf[i] == '\r') {
                continue;
            }
            if (currentLength == expectedLength) {
                skip = 1;
                continue;
            }
            if (buf[i] != word[currentLength]) {
                same = 0;
            }
            current[currentLength] = buf[i];
            if (actual[buf[i]] < modifier) {
                actual[buf[i]] = modifier;
            }
            actual[buf[i]]++;
            if (actual[buf[i]] > expected[buf[i]] + modifier) {
                skip = 1;
            }
            currentLength++;
        }
    }
    fclose(file);
    gettimeofday(&stop, NULL);
    printf("%.0lf%s\n", timeDiff(start, stop), csv);

    return 0;
}
