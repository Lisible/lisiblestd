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
#define LSTD_LOG_LEVEL LogLevel_Trace

#define LOG0(log_level, msg)                                                   \
  do {                                                                         \
    if (LSTD_LOG_LEVEL <= log_level) {                                         \
      fprintf(stderr, LSTD_LOG_PREFIX "%s\n", log_level_to_str(log_level),     \
              __FILE__, __LINE__, msg);                                        \
    }                                                                          \
  } while (0)
#define LOG0_TRACE(msg) LOG0(LogLevel_Trace, msg)
#define LOG0_DEBUG(msg) LOG0(LogLevel_Debug, msg)
#define LOG0_WARN(msg) LOG0(LogLevel_Warn, msg)
#define LOG0_ERROR(msg) LOG0(LogLevel_Error, msg)
#define LOG0_INFO(msg) LOG0(LogLevel_Info, msg)

#define LOG(log_level, fmt, ...)                                               \
  do {                                                                         \
    if (LSTD_LOG_LEVEL <= log_level) {                                         \
      fprintf(stderr, LSTD_LOG_PREFIX fmt "\n", log_level_to_str(log_level),   \
              __FILE__, __LINE__, __VA_ARGS__);                                \
    }                                                                          \
  } while (0)
#define LOG_TRACE(fmt, ...) LOG(LogLevel_Trace, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(LogLevel_Debug, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG(LogLevel_Warn, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(LogLevel_Error, fmt, __VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG(LogLevel_Info, fmt, __VA_ARGS__)

const char *log_level_to_str(LogLevel log_level);

#endif // LSTD_LOG_H
