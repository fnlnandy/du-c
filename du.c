#include <stdio.h>
#include <string.h>

#include "du.h"
#include "file.h"

#define STR_EQ 0

int main(int argc, char **argv)
{
    argc--, argv++;

    if (argc == 0)
    {
        puts("Usage: du-c [FILE]");
        return 0;
    }

    uint32_t forcedType = GIGABYTE + 1; // Aka INVALID.
    char *filePath = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "-b", 2) == STR_EQ)
        {
            forcedType = BYTE;
        }
        else if (strncmp(argv[i], "-k", 2) == STR_EQ)
        {
            forcedType = KILOBYTE;
        }
        else if (strncmp(argv[i], "-m", 2) == STR_EQ)
        {
            forcedType = MEGABYTE;
        }
        else if (strncmp(argv[i], "-g", 2) == STR_EQ)
        {
            forcedType = GIGABYTE;
        }
        // If this string is not a default argument,
        // and not an argument, then we got our
        // filename supposedly.
        else if (strncmp(argv[i], "-", 1) != STR_EQ)
        {
            filePath = argv[i];
        }
    }

    displayFileSize(filePath, forcedType);

    return 0;
}