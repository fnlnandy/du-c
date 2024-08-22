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

sizeinfo_t displayDirSize(const char *dirPath, enum SizeCategory forcedType, boolean ignoreHiddenFiles)
{
    DIR *dir = tryToOpenDir(dirPath);
    struct dirent *entry = NULL;
    sizeinfo_t dirSize = {.sizeCat = BYTE, .sizeVal = 0};

    // Parsing every entry, since we need the sum to "approximately"
    // guess the size of the passed directory.
    for (entry = readdir(dir); entry != NULL; entry = readdir(dir))
    {
        // Compares the entry with the current directory (i.e. '.'), if
        // it's equal then we ignore it.
        if (strlen(entry->d_name) == 1 && entry->d_name[0] == CWD_)
            continue;
        // Compares the entry with the parent directory, if it's equal then we
        // ignore it.
        if (strlen(entry->d_name) == 2 && strncmp(entry->d_name, POWD, 2) == STR_EQ)
            continue;

        if (ignoreHiddenFiles == B_TRUE && strlen(entry->d_name) >= 2 && entry->d_name[0] == '.' && entry->d_name[1] != '/')
            continue;

        if (entry->d_type == TYPE_FILE)
            dirSize.sizeVal += displayFileSize(concatenateDirPath(dirPath, entry->d_name), BYTE).sizeVal;
        else if (entry->d_type == TYPE_DIR)
            dirSize.sizeVal += displayDirSize(concatenateDirPath(dirPath, entry->d_name), BYTE, ignoreHiddenFiles).sizeVal;
    }

    // By default, the sizes are in bytes, we just need to force this
    // one to comply to the category we want.
    dirSize = forceSizeInfo(dirSize.sizeVal, forcedType);

    if (closedir(dir) != 0)
        FATAL("Unexpected error while closing directory '%s'. Aborting.\n", dirPath);

    printf(OUTFMT, dirSize.sizeVal, getSizeStr(dirSize).sizeStr, dirPath);

    return dirSize;
}

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