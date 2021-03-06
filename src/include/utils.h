#ifndef ESTER_UTILS_H
#define ESTER_UTILS_H

#include <stdio.h>

#ifdef DEBUG
#define ester_err(...) do { \
    fprintf(stderr, "Error at %s:%d: ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while(0)
#else
#define ester_err(...) do { \
    fprintf(stderr, "Error: "); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while(0)
#endif

#ifdef DEBUG
#define ester_warn(...) do { \
    fprintf(stderr, "Warning at %s:%d: ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while(0)
#else
#define ester_warn(...) do { \
    fprintf(stderr, "Warning: "); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while(0)
#endif

#ifdef DEBUG
#define ester_debug(...) do { \
    fprintf(stderr, __VA_ARGS__); \
} while (0)
#else
#define ester_debug(...) do {} while (0)
#endif

bool isHDF5Name(const char *fileName);

#endif // ESTER_UTILS_H
