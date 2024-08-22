#include <stdio.h>
#include <string.h>

#include "du.h"
#include "file.h"
#include "dir.h"

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

    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "-b", 2) == STR_EQ)
            forcedType = BYTE;
        else if (strncmp(argv[i], "-k", 2) == STR_EQ)
            forcedType = KILOBYTE;
        else if (strncmp(argv[i], "-m", 2) == STR_EQ)
            forcedType = MEGABYTE;
        else if (strncmp(argv[i], "-g", 2) == STR_EQ)
            forcedType = GIGABYTE;
        // If this string is not a default argument,
        // and not an argument, then we got our
        // filename supposedly.
        else if (strncmp(argv[i], "-", 1) != STR_EQ)
            filePath = argv[i];
    }

    if (filePath == NULL || strncmp(filePath, ".", 1) == STR_EQ)
    {
        displayDirSize(".", forcedType);
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
        displayDirSize(filePath, forcedType);
    }

    return 0;
}