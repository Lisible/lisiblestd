#ifndef LSTD_LOG_H
#define LSTD_LOG_H

#include <stdio.h>

#define LSTD_LOG_PREFIX "[%s %s:%d] "

typedef enum {
  LogLevel_Trace = 0,
  LogLevel_Debug,
  LogLevel_Warn,
  LogLevel_Error,
  LogLevel_Info
} LogLevel;

extern LogLevel lstd_log_level;

#ifdef LSTD_PLATFORM_PLAYDATE
#include <pd_api.h>
extern PlaydateAPI *pd;
#define LOG(log_level, ...)                                                    \
  do {                                                                         \
    if (lstd_log_level <= log_level) {                                         \
      pd->system->logToConsole(LSTD_LOG_PREFIX, log_level_to_str(log_level),   \
                               __FILE__, __LINE__);                            \
      pd->system->logToConsole(__VA_ARGS__);                                   \
      pd->system->logToConsole("\n");                                          \
    }                                                                          \
  } while (0)
#else
#define LOG(log_level, ...)                                                    \
  do {                                                                         \
    if (lstd_log_level <= log_level) {                                         \
      fprintf(stderr, LSTD_LOG_PREFIX, log_level_to_str(log_level), __FILE__,  \
              __LINE__);                                                       \
      fprintf(stderr, __VA_ARGS__);                                            \
      fprintf(stderr, "\n");                                                   \
    }                                                                          \
  } while (0)
#endif
#define LOG_TRACE(...) LOG(LogLevel_Trace, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LogLevel_Debug, __VA_ARGS__)
#define LOG_WARN(...) LOG(LogLevel_Warn, __VA_ARGS__)
#define LOG_ERROR(...) LOG(LogLevel_Error, __VA_ARGS__)
#define LOG_INFO(...) LOG(LogLevel_Info, __VA_ARGS__)

void lstd_log_init(void);
const char *log_level_to_str(LogLevel log_level);
LogLevel log_level_from_str(const char *str);

#endif // LSTD_LOG_H
