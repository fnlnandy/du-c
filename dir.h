#ifndef GUARD_DIR_H_INCLUDED
#define GUARD_DIR_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "du.h"
#include "file.h"

sizeinfo_t displayDirSize(const char *dirPath, enum SizeCategory forcedType);
DIR *tryToOpenCurrentDir();
DIR *tryToOpenDir(const char *dirPath);

enum EntType
{
    TYPE_DIR = 4,
    TYPE_FILE = 8,
};

#endif // GUARD_DIR_H_INCLUDED