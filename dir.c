#include <stdlib.h>

#include "dir.h"

static char *concatenateDirPath(const char *dir, const char *nextEnt)
{
    const uint32_t dirLen = strlen(dir);
    const uint32_t nextEntLen = strlen(nextEnt);
    const uint32_t size = dirLen + nextEntLen + 1 + 2;
    char *dirPath = malloc(size);

    strcpy(dirPath, dir);
    dirPath[dirLen] = '/';
    strcpy(dirPath + dirLen + 1, nextEnt);

    dirPath[size - 1] = '\0';
    return dirPath;
}

sizeinfo_t displayDirSize(const char *dirPath, enum SizeCategory forcedType)
{
    DIR *dir = tryToOpenDir(dirPath);
    struct dirent *entry = NULL;
    sizeinfo_t dirSize = {.sizeCat = BYTE, .sizeVal = 0};

    for (entry = readdir(dir); entry != NULL; entry = readdir(dir))
    {
        // CWD and parent directory are NOT to be parsed.
        if (strncmp(entry->d_name, "..", 2) == 0 || strncmp(entry->d_name, ".", 1) == 0)
            continue;
        else if (entry->d_type == TYPE_FILE)
            dirSize.sizeVal += displayFileSize(concatenateDirPath(dirPath, entry->d_name), BYTE).sizeVal;
        else if (entry->d_type == TYPE_DIR)
            dirSize.sizeVal += displayDirSize(concatenateDirPath(dirPath, entry->d_name), BYTE).sizeVal;
    }

    // By default, the sizes are in bytes, we just need to force this
    // one to comply to the category we want.
    dirSize = forceSizeInfo(dirSize.sizeVal, forcedType);

    if (closedir(dir) != 0)
        FATAL("Unexpected error while closing directory '%s'. Aborting.\n", dirPath);

    printf("%d %s -> %s\n", dirSize.sizeVal, getSizeStr(dirSize).sizeStr, dirPath);

    return dirSize;
}

#define CWD "."

DIR *tryToOpenCurrentDir()
{
    return tryToOpenDir(CWD);
}

DIR *tryToOpenDir(const char *dirPath)
{
    DIR *stream = opendir(dirPath);

    if (stream == NULL)
        FATAL("Impossible to open directory '%s'. Aborting.\n", dirPath);

    return stream;
}