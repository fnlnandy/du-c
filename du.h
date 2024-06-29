#ifndef GUARD_DU_H_INCLUDED
#define GUARD_DU_H_INCLUDED

#define UNUSED(var) (void)(var)

#define FATAL(fmt, ...)                    \
    {                                      \
        fprintf(stderr, fmt, __VA_ARGS__); \
        exit(1);                           \
    }

#endif // GUARD_DU_H_INCLUDED