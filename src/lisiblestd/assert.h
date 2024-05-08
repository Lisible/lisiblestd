#ifndef LSTD_ASSERT_H
#define LSTD_ASSERT_H

#include "log.h"

extern void exit(int);

#define LSTD_ASSERT(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      LOG("Assertion failed:\n\t%s", #expr);                                   \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define LSTD_UNIMPLEMENTED()                                                   \
  do {                                                                         \
    LOG0("Unimplemented code reached");                                        \
    exit(1);                                                                   \
  } while (0)

#endif // LSTD_ASSERT_H
