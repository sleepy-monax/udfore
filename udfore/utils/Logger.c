#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "udfore/utils/Logger.h"

static int _log_level;

static const char *level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

void logger_set_level(int level)
{
    _log_level = level;
}

void logger_log(int level, const char *file, int line, const char *fmt, ...)
{
    if (level < _log_level)
    {
        return;
    }

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

    fprintf(
        stderr, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
        buf, level_colors[level], level_names[level], file, line);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
}
