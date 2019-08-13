#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

static struct
{
    FILE *fp;
    int level;
    int quiet;
} L;

static const char *level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

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

void logger_set_fp(FILE *fp)
{
    L.fp = fp;
}

void logger_set_level(int level)
{
    L.level = level;
}

void logger_set_quiet(int enable)
{
    L.quiet = enable ? 1 : 0;
}

void logger_log(int level, const char *file, int line, const char *fmt, ...)
{
    if (level < L.level)
    {
        return;
    }

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    /* Log to stderr */
    if (!L.quiet)
    {
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

    /* Log to file */
    if (L.fp)
    {
        va_list args;
        char buf[32];
        buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
        fprintf(L.fp, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
        va_start(args, fmt);
        vfprintf(L.fp, fmt, args);
        va_end(args);
        fprintf(L.fp, "\n");
        fflush(L.fp);
    }
}