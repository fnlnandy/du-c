#include <stdlib.h>

#include "dir.h"

sizeinfo_t displayDirSize(const char *dirPath, enum SizeCategory forcedType)
{
    DIR *dir = tryToOpenDir(dirPath);
    struct dirent *entry = NULL;
    sizeinfo_t dirSize = {.sizeCat = BYTE, .sizeVal = 0};

    for (entry = readdir(dir); entry != NULL; entry = readdir(dir))
    {
        if (strncmp(entry->d_name, "..", 2) == 0 || strncmp(entry->d_name, ".", 1) == 0)
            continue;
        else if (entry->d_type == TYPE_FILE)
            dirSize.sizeVal += displayFileSize(entry->d_name, BYTE).sizeVal;
        else if (entry->d_type == TYPE_DIR)
            dirSize.sizeVal += displayDirSize(entry->d_name, BYTE).sizeVal;
    }

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