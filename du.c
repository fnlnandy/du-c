#include <stdio.h>
#include <string.h>

#include "du.h"
#include "file.h"
#include "dir.h"

/**
 * @brief Helper function for strncmp,
 * basically emits the argument and its size
 * based on sizeof.
 */
#define EMITARGSIZE(arg) "" arg "", sizeof(arg)

int main(int argc, char **argv)
{
    argc--, argv++;

    if (argc == 0)
    {
        puts("Usage: du-c [FILE] [-b/-k/-m/-g]");
        return 0;
    }

    uint32_t forcedType = GIGABYTE + 1; // Aka INVALID.
    char *filePath = NULL;
    boolean ignoreHiddenFiles = B_TRUE;

    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], EMITARGSIZE("-b")) == STR_EQ)
            forcedType = BYTE;
        else if (strncmp(argv[i], EMITARGSIZE("-k")) == STR_EQ)
            forcedType = KILOBYTE;
        else if (strncmp(argv[i], EMITARGSIZE("-m")) == STR_EQ)
            forcedType = MEGABYTE;
        else if (strncmp(argv[i], EMITARGSIZE("-g")) == STR_EQ)
            forcedType = GIGABYTE;
        else if (strncmp(argv[i], EMITARGSIZE("--show-hidden")) == STR_EQ)
            ignoreHiddenFiles = B_FALSE;
        // If this string is not a default argument,
        // and not an argument, then we got our
        // filename supposedly.
        else if (strncmp(argv[i], "-", 1) != STR_EQ)
            filePath = argv[i];
    }

    if (filePath == NULL || strncmp(filePath, ".", 1) == STR_EQ)
    {
        displayDirSize(".", forcedType, ignoreHiddenFiles);
        return 0;
    }

    DIR *stream = opendir(filePath);

    // We're encountering a file, not a directory.
    if (stream == NULL)
    {
        displayFileSize(filePath, forcedType);
    }
    else
    {
        closedir(stream);
        displayDirSize(filePath, forcedType, ignoreHiddenFiles);
    }

    return 0;
}