#ifndef GUARD_DIR_H_INCLUDED
#define GUARD_DIR_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "du.h"
#include "file.h"

/**
 * @param dirPath
 * @param forcedType
 * @param ignoreHiddenFiles
 *
 * @brief Displays the size of a specific
 * directory (by adding its members').
 *
 * @returns sizeinfo_t
 */
sizeinfo_t displayDirSize(const char *dirPath, enum SizeCategory forcedType, boolean ignoreHiddenFiles);
/**
 * @brief Tries to open the current working
 * directory.
 *
 * @details This is just a call to tryToOpenDir()
 * with '.' as argument (the current working
 * directory.).
 *
 * @returns DIR *
 */
DIR *tryToOpenCurrentDir();
/**
 * @param dirPath
 *
 * @brief Tries to open a DIR *
 * stream from the given dirPath.
 *
 * @returns DIR *
 *
 * @warning On failure, this function
 * will emit a FATAL error.
 */
DIR *tryToOpenDir(const char *dirPath);

/**
 * @brief Constants for the different
 * types that can be assigned to
 * `struct dirent { .d_type = ... }`.
 *
 * @todo Add TYPE_UNKNOWN.
 */
enum EntType
{
    TYPE_DIR = 4,
    TYPE_FILE = 8,
};

#endif // GUARD_DIR_H_INCLUDED