#include <stdio.h>
#include <stdlib.h>
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

static void printUsageAndExit(void);
static void parseProgArgs(int argc, char **argv, char **filePath, uint32_t *forcedType, boolean *ignoreHiddenFiles);

int main(int argc, char **argv)
{
    argc--, argv++;

    char *filePath = NULL;
    uint32_t forcedType = GIGABYTE + 1; // Aka INVALID.
    boolean ignoreHiddenFiles = B_TRUE;

    parseProgArgs(argc, argv, &filePath, &forcedType, &ignoreHiddenFiles);

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

static void printUsageAndExit(void)
{
    puts("Usage: du-c FILE/DIRECTORY [-b/-k/-m/-g] [--show-hidden]");
    exit(0);
}

static inline boolean isArg(const char *src, const char *targetArg)
{
    return strncmp(src, targetArg, strlen(targetArg)) == STR_EQ;
}

static void parseProgArgs(int argc, char **argv, char **filePath, uint32_t *forcedType, boolean *ignoreHiddenFiles)
{
    if (argc == 0)
        printUsageAndExit();

    for (int i = 0; i < argc; ++i)
    {
        char *current = argv[i];

        if (isArg(current, "-?") || isArg(current, "-h") || isArg(current, "--help"))
            printUsageAndExit();

        if (isArg(current, "-b"))
            *forcedType = BYTE;
        else if (isArg(current, "-k"))
            *forcedType = KILOBYTE;
        else if (isArg(current, "-m"))
            *forcedType = MEGABYTE;
        else if (isArg(current, "-g"))
            *forcedType = GIGABYTE;
        else if (isArg(current, "--show-hidden"))
            *ignoreHiddenFiles = B_FALSE;
        else if (current[0] != '-')
            *filePath = current;
        else
            FATAL("Unrecognized argument(s). First one being: '%s'. Aborting.\n", current);
    }
}