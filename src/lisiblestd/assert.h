#ifndef LSTD_ASSERT_H
#define LSTD_ASSERT_H

#include "log.h"

extern void exit(int);



#ifdef LSTD_PLATFORM_PLAYDATE
#include <pd_api.h>
extern PlaydateAPI* pd;
#define LSTD_ASSERT(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      pd->system->error("Assertion failed:\n\t%s", #expr);                     \
    }                                                                          \
  } while (0)

#define LSTD_UNIMPLEMENTED()                                                   \
  do {                                                                         \
      pd->system->error("Unimpemented code reached");                          \
  } while (0)
#else
#define LSTD_ASSERT(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      LOG_ERROR("Assertion failed:\n\t%s", #expr);                             \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define LSTD_UNIMPLEMENTED()                                                   \
  do {                                                                         \
    LOG_ERROR("Unimplemented code reached");                                   \
    exit(1);                                                                   \
  } while (0)
#endif

#endif // LSTD_ASSERT_H
