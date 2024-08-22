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
#define FATAL(fmt, ...)                    \
    {                                      \
        fprintf(stderr, fmt, __VA_ARGS__); \
        exit(1);                           \
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

#endif // GUARD_DU_H_INCLUDED