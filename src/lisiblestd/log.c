#include "log.h"

const char *log_level_to_str(LogLevel log_level) {
  switch (log_level) {
  case LogLevel_Trace:
    return "TRACE";
  case LogLevel_Debug:
    return "DEBUG";
  case LogLevel_Warn:
    return "WARN";
  case LogLevel_Error:
    return "ERROR";
  case LogLevel_Info:
  default:
    return "INFO";
    break;
  }
}
