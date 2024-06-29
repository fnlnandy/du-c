#include <stdlib.h>

#include "du.h"
#include "file.h"

void displayFileSize(const char *filePath, enum SizeCategory forcedType)
{
    FILE *toDisplay = tryToOpenFile(filePath);
    uint32_t fileSize = getFileSize(toDisplay);
    sizeinfo_t sizeInfo;
    sizestr_t sizeStr;

    if (forcedType > GIGABYTE)
        sizeInfo = getSizeInfo(fileSize);
    else
        sizeInfo = forceSizeInfo(fileSize, forcedType);

    sizeStr = getSizeStr(sizeInfo);

    printf("%d %s -> %s\n", sizeInfo.sizeVal, sizeStr.sizeStr, filePath);
    return;
}

FILE *tryToOpenFile(const char *filePath)
{
    FILE *file = fopen(filePath, "r");

    if (file == NULL)
        FATAL("Unable to open file: '%s'. Aborting.\n", filePath);

    return file;
}

uint32_t getFileSize(FILE *file)
{
    uint32_t savedPos, fileSize;

    savedPos = ftell(file);

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);

    fseek(file, savedPos, SEEK_SET);

    return fileSize;
}

static const uint32_t sPowers[] = {1, 1024, 1048576, 1073741824};

sizeinfo_t getSizeInfo(const uint32_t rawSize)
{
    sizeinfo_t sizeInfo = {.sizeVal = rawSize, .sizeCat = BYTE};

    // We ignore the byte, since it is the default
    // datatype.
    for (uint32_t i = GIGABYTE; i > BYTE; i--)
    {
        if (sizeInfo.sizeVal / sPowers[i] > 0)
        {
            sizeInfo.sizeCat = i;
            break;
        }
    }

    sizeInfo.sizeVal /= sPowers[sizeInfo.sizeCat];

    return sizeInfo;
}

sizeinfo_t forceSizeInfo(const uint32_t rawSize, enum SizeCategory category)
{
    sizeinfo_t forced = {.sizeVal = rawSize, .sizeCat = BYTE};

    if (category == BYTE || category > GIGABYTE)
        return forced;

    forced.sizeCat = category;
    forced.sizeVal /= sPowers[category];
    return forced;
}

// TODO: Since this was for sprintf, we don't
// need it anymore, hence this should be a char *.
sizestr_t getSizeStr(const sizeinfo_t sizeInfo)
{
    sizestr_t sizeStr = {.sizeStr = NULL, .strLen = 0};

    switch (sizeInfo.sizeCat)
    {
    case KILOBYTE:
        sizeStr.sizeStr = "KB";
        sizeStr.strLen = 2;
        break;
    case MEGABYTE:
        sizeStr.sizeStr = "MB";
        sizeStr.strLen = 2;
        break;
    case GIGABYTE:
        sizeStr.sizeStr = "GB";
        sizeStr.strLen = 2;
        break;
    default:
        sizeStr.sizeStr = "B";
        sizeStr.strLen = 1;
        break;
    }

    return sizeStr;
}
