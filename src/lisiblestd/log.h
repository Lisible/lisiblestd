#ifndef LSTD_LOG_H
#define LSTD_LOG_H

#include <stdio.h>

#define LOG_PREFIX "[%s:%d] "

#define LOG0(msg)                                                              \
  do {                                                                         \
    fprintf(stderr, LOG_PREFIX "%s\n", __FILE__, __LINE__, msg);               \
  } while (0)

#define LOG(fmt, ...)                                                          \
  do {                                                                         \
    fprintf(stderr, LOG_PREFIX fmt "\n", __FILE__, __LINE__, __VA_ARGS__);     \
  } while (0)

#endif // LSTD_LOG_H
