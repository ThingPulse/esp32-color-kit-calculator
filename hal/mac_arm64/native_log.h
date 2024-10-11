#ifndef NATIVE_LOG_H
#define NATIVE_LOG_H

#include <stdio.h>


// Define log levels
#define LOG_LEVEL_VERBOSE 0
#define LOG_LEVEL_DEBUG   1
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_WARN    3
#define LOG_LEVEL_ERROR   4

// Set the current log level here (can be modified for different builds)
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_VERBOSE
#endif

// Macros for logging, each checks the current log level and prints if the level is allowed

#define log_i(tag, fmt, ...) \
    do { if (CURRENT_LOG_LEVEL <= LOG_LEVEL_VERBOSE) \
        printf("[VERBOSE] [%s] " fmt "\n", tag, ##__VA_ARGS__); \
    } while(0)

#define log_d(tag, fmt, ...) \
    do { if (CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG) \
        printf("[DEBUG] [%s] " fmt "\n", tag, ##__VA_ARGS__); \
    } while(0)

#define log_i(tag, fmt, ...) \
    do { if (CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO) \
        printf("[INFO] [%s] " fmt "\n", tag, ##__VA_ARGS__); \
    } while(0)

#define log_w(tag, fmt, ...) \
    do { if (CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN) \
        printf("[WARN] [%s] " fmt "\n", tag, ##__VA_ARGS__); \
    } while(0)

#define log_e(tag, fmt, ...) \
    do { if (CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR) \
        printf("[ERROR] [%s] " fmt "\n", tag, ##__VA_ARGS__); \
    } while(0)

#endif // NATIVE_LOG_H
