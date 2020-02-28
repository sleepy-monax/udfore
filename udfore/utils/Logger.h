#pragma once

enum
{
    LOGGER_TRACE,
    LOGGER_DEBUG,
    LOGGER_INFO,
    LOGGER_WARN,
    LOGGER_ERROR,
    LOGGER_FATAL
};

#define logger_trace(...) logger_log(LOGGER_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define logger_debug(...) logger_log(LOGGER_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define logger_info(...) logger_log(LOGGER_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define logger_warn(...) logger_log(LOGGER_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define logger_error(...) logger_log(LOGGER_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define logger_fatal(...) logger_log(LOGGER_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void logger_set_level(int level);

void logger_log(int level, const char *file, int line, const char *fmt, ...);
