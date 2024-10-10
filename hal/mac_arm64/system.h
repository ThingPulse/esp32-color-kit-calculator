#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Define the delay macro to pause execution for the specified number of milliseconds
#ifdef _WIN32
#define delay(ms) Sleep(ms)
#else
#define delay(ms) usleep((ms) * 1000)  // Convert milliseconds to microseconds
#endif

// Macro to get the minimum of two values
#define _min(a, b) ((a) < (b) ? (a) : (b))

// Macro to get the maximum of two values
#define _max(a, b) ((a) > (b) ? (a) : (b))

#endif // SYSTEM_H
