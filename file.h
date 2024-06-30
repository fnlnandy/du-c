#ifndef GUARD_FILE_H_INCLUDED
#define GUARD_FILE_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

enum SizeCategory
{
    BYTE,
    KILOBYTE,
    MEGABYTE,
    GIGABYTE
};

typedef struct
{
    uint32_t sizeVal;
    enum SizeCategory sizeCat;
} sizeinfo_t;

typedef struct
{
    char *sizeStr;
    uint32_t strLen;
} sizestr_t;

sizeinfo_t displayFileSize(const char *filePath, enum SizeCategory forcedType);
FILE *tryToOpenFile(const char *filePath);
uint32_t getFileSize(FILE *file);
sizeinfo_t getSizeInfo(const uint32_t rawSize);
sizeinfo_t forceSizeInfo(const uint32_t rawSize, enum SizeCategory category);
sizestr_t getSizeStr(const sizeinfo_t sizeInfo);

#endif // GUARD_FILE_H_INCLUDED
