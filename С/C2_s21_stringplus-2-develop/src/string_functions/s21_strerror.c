#include "../s21_string.h"

#ifdef __linux__
static const char *linux_error_list[] = {
    "Success",                            // 0
    "Operation not permitted",            // 1
    "No such file or directory",          // 2
    "No such process",                    // 3
    "Interrupted system call",            // 4
    "Input/output error",                 // 5
    "No such device or address",          // 6
    "Argument list too long",             // 7
    "Exec format error",                  // 8
    "Bad file descriptor",                // 9
    "No child processes",                 // 10
    "Resource temporarily unavailable",   // 11
    "Cannot allocate memory",             // 12
    "Permission denied",                  // 13
    "Bad address",                        // 14
    "Block device required",              // 15
    "Device or resource busy",            // 16
    "File exists",                        // 17
    "Invalid cross-device link",          // 18
    "No such device",                     // 19
    "Not a directory",                    // 20
    "Is a directory",                     // 21
    "Invalid argument",                   // 22
    "Too many open files in system",      // 23
    "Too many open files",                // 24
    "Inappropriate ioctl for device",     // 25
    "Text file busy",                     // 26
    "File too large",                     // 27
    "No space left on device",            // 28
    "Illegal seek",                       // 29
    "Read-only file system",              // 30
    "Too many links",                     // 31
    "Broken pipe",                        // 32
    "Numerical argument out of domain",   // 33
    "Numerical result out of range",      // 34
    "Resource deadlock avoided",          // 35
    "File name too long",                 // 36
    "No locks available",                 // 37
    "Function not implemented",           // 38
    "Directory not empty",                // 39
    "Too many levels of symbolic links",  // 40
    "Unknown error 1000",                 // 41
};

#elif defined(__APPLE__)
static const char *apple_error_list[] = {
    "Undefined error: 0",                 // 0
    "Operation not permitted",            // 1
    "No such file or directory",          // 2
    "No such process",                    // 3
    "Interrupted system call",            // 4
    "Input/output error",                 // 5
    "Device not configured",              // 6
    "Argument list too long",             // 7
    "Exec format error",                  // 8
    "Bad file descriptor",                // 9
    "No child processes",                 // 10
    "Resource deadlock avoided",          // 11
    "Cannot allocate memory",             // 12
    "Permission denied",                  // 13
    "Bad address",                        // 14
    "Block device required",              // 15
    "Resource busy",                      // 16
    "File exists",                        // 17
    "Cross-device link",                  // 18
    "Operation not supported by device",  // 19
    "Not a directory",                    // 20
    "Is a directory",                     // 21
    "Invalid argument",                   // 22
    "Too many open files in system",      // 23
    "Too many open files",                // 24
    "Inappropriate ioctl for device",     // 25
    "Text file busy",                     // 26
    "File too large",                     // 27
    "No space left on device",            // 28
    "Illegal seek",                       // 29
    "Read-only file system",              // 30
    "Too many links",                     // 31
    "Broken pipe",                        // 32
    "Numerical argument out of domain",   // 33
    "Result too large",                   // 34
    "Resource temporarily unavailable",   // 35
    "Operation now in progress",          // 36
    "Operation already in progress",      // 37
    "Socket operation on non-socket",     // 38
    "Destination address required",       // 39
    "Message too long",                   // 40
    "Unknown error",                      // 41
};
#endif

char *s21_strerror(int errnum) {
  static char buffer[100];
  const char *error_message = "Unknown error 1000";
  int max_errnum = 41;

#ifdef __linux__
  if (errnum >= 0 && errnum <= max_errnum) {
    error_message = linux_error_list[errnum];
  }
#elif defined(__APPLE__)
  if (errnum >= 0 && errnum <= max_errnum) {
    error_message = apple_error_list[errnum];
  }
#endif

  snprintf(buffer, sizeof(buffer), "%s", error_message);
  return buffer;
}