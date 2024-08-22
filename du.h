#ifndef GUARD_DU_H_INCLUDED
#define GUARD_DU_H_INCLUDED

/**
 * @brief Macro to remove unused
 * variable warnings.
 */
#define UNUSED(var) (void)(var)

/**
 * @brief Macro that outputs a fatal
 * error to stderr and quits the program.
 */
#define FATAL(fmt, ...)                              \
    {                                                \
        fprintf(stderr, "FATAL: " fmt, __VA_ARGS__); \
        exit(1);                                     \
    }

/**
 * @brief This is the result of an
 * str[n]cmp*, when the strings are equal.
 */
#define STR_EQ 0

/**
 * @brief Represents the current working
 * directory.
 */
#define CWD "."
#define CWD_ '.'

/**
 * @brief Represents the parent directory.
 *
 * @todo Find a better name ?
 */
#define POWD ".."

/**
 * @brief Represents the default output of
 * a file/directory's size.
 */
#define OUTFMT "%d %s\t\t%s\n"

/**
 * @brief Placeholder name for the boolean
 * type.
 */
typedef unsigned char boolean;

/**
 * @brief The states a boolean can take.
 */
enum
{
    B_FALSE,
    B_TRUE
};

#endif // GUARD_DU_H_INCLUDED