#ifndef GUARD_FILE_H_INCLUDED
#define GUARD_FILE_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Categories constants.
 */
enum SizeCategory
{
    BYTE,
    KILOBYTE,
    MEGABYTE,
    GIGABYTE
};

/**
 * @brief Base struct that contains
 * a file / directory's size info.
 */
typedef struct
{
    uint32_t sizeVal;
    enum SizeCategory sizeCat;
} sizeinfo_t;

/**
 * @brief Base struct that will
 * contain a string's info when printing.
 *
 * @todo Get rid of this.
 */
typedef struct
{
    char *sizeStr;
    uint32_t strLen;
} sizestr_t;

/**
 * @param filePath
 * @param forcedType
 *
 * @brief Displays the size of
 * a specific file.
 *
 * @returns sizeintot_t
 */
sizeinfo_t displayFileSize(const char *filePath, enum SizeCategory forcedType);
/**
 * @param filePath
 *
 * @brief Tries to open a FILE *
 * stream.
 *
 * @returns FILE *
 *
 * @warning This will emit a FATAL
 * error on failure.
 */
FILE *tryToOpenFile(const char *filePath);
/**
 * @param file
 *
 * @brief Gets the size of a FILE *
 * stream.
 *
 * @returns uint32_t
 */
uint32_t getFileSize(FILE *file);
/**
 * @param rawSize
 *
 * @brief Gets the adequate size info
 * for a raw size argument.
 *
 * @returns sizeinfo_t
 */
sizeinfo_t getSizeInfo(const uint32_t rawSize);
/**
 * @param rawSize
 * @param category
 *
 * @brief Forcibly makes the value
 * comply to the passed category.
 *
 * @returns sizeinfo_t
 */
sizeinfo_t forceSizeInfo(const uint32_t rawSize, enum SizeCategory category);
/**
 * @param sizeInfo
 *
 * @brief Gets the corresponding string
 * to the current sizeinfo_t data.
 *
 * @returns sizestr_t
 *
 * @todo Make this return a simple char *.
 */
sizestr_t getSizeStr(const sizeinfo_t sizeInfo);

#endif // GUARD_FILE_H_INCLUDED
