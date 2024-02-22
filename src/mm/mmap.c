// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>
#include <internal/string.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	/* TODO: Implement mmap(). */
    long ret = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
    if (ret < 0) {
        errno = -(int)ret;
        return MAP_FAILED;
    }

    return (void*) ret;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	void *new_address;
    int ret;

    new_address = mmap(NULL, new_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_address == MAP_FAILED) {
        return MAP_FAILED;
    }

    ret = syscall(__NR_mprotect, new_address, new_size, PROT_READ | PROT_WRITE);
    if (ret < 0) {
        munmap(new_address, new_size);
        return MAP_FAILED;
    }

    if (old_size > new_size) {
        old_size = new_size;
    }

    if (old_address != NULL) {
        memcpy(new_address, old_address, old_size);
        munmap(old_address, old_size);
    }

    return new_address;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	int ret = syscall(__NR_munmap, addr, length);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return 0;
}
