#ifndef _TIME_H
#define _TIME_H

#include <stddef.h>

typedef long time_t;

struct timespec {
    time_t tv_sec;      /* seconds */
    long tv_nsec;       /* nanoseconds */
};

int nanosleep(const struct timespec *req, struct timespec *rem);
unsigned int sleep(unsigned int seconds);

#endif /* _TIME_H */
