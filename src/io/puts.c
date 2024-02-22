#include <stdio.h>
#include <string.h>
#include <errno.h>

int puts(const char *str) {
    size_t len = strlen(str);
    size_t n = write(1, str, len);
    if (n == -1) {
        errno = EIO;
        return -1;
    }
    n += write(1, "\n", 1);
    if (n == -1) {
        errno = EIO;
        return -1;
    }
    return n;
}
