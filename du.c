#include <stdio.h>
#include <string.h>

#include "du.h"
#include "file.h"

int main(int argc, char **argv)
{
    argc--, argv++;

    if (argc == 0)
    {
        puts("Usage: du-c [FILE]");
        return 0;
    }

    displayFileSize(argv[0]);

    return 0;
}