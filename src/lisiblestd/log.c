#include "log.h"
#include <stdlib.h>
#include <string.h>

LogLevel lstd_log_level = LogLevel_Info;

void lstd_log_init(void) {
  const char *log_level_str = getenv("LSTD_LOG");
  if (log_level_str) {
    lstd_log_level = log_level_from_str(log_level_str);
  }
}

const char *LSTD_LOG_LEVEL_STR_TRACE = "TRACE";
const char *LSTD_LOG_LEVEL_STR_DEBUG = "DEBUG";
const char *LSTD_LOG_LEVEL_STR_WARN = "WARN";
const char *LSTD_LOG_LEVEL_STR_ERROR = "ERROR";
const char *LSTD_LOG_LEVEL_STR_INFO = "INFO";

const char *log_level_to_str(LogLevel log_level) {
  switch (log_level) {
  case LogLevel_Trace:
    return LSTD_LOG_LEVEL_STR_TRACE;
  case LogLevel_Debug:
    return LSTD_LOG_LEVEL_STR_DEBUG;
  case LogLevel_Warn:
    return LSTD_LOG_LEVEL_STR_WARN;
  case LogLevel_Error:
    return LSTD_LOG_LEVEL_STR_ERROR;
  case LogLevel_Info:
  default:
    return LSTD_LOG_LEVEL_STR_INFO;
    break;
  }
}

LogLevel log_level_from_str(const char *str) {
  if (strncmp(str, LSTD_LOG_LEVEL_STR_TRACE,
              strlen(LSTD_LOG_LEVEL_STR_TRACE)) == 0) {
    return LogLevel_Trace;
  } else if (strncmp(str, LSTD_LOG_LEVEL_STR_DEBUG,
                     strlen(LSTD_LOG_LEVEL_STR_DEBUG)) == 0) {
    return LogLevel_Debug;
  } else if (strncmp(str, LSTD_LOG_LEVEL_STR_WARN,
                     strlen(LSTD_LOG_LEVEL_STR_WARN)) == 0) {
    return LogLevel_Warn;
  } else if (strncmp(str, LSTD_LOG_LEVEL_STR_ERROR,
                     strlen(LSTD_LOG_LEVEL_STR_ERROR)) == 0) {
    return LogLevel_Error;
  }

  return LogLevel_Info;
}
