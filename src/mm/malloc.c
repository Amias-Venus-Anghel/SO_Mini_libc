// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

static int mem_list_initialized = 0;

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	if (!mem_list_initialized) {
        mem_list_init();
        mem_list_initialized = 1;
    }

    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }

    if (mem_list_add(mem, size) < 0) {
        munmap(mem, size);
        return NULL;
    }

    return mem;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	size_t total_size = nmemb * size;

    void *ptr = malloc(total_size);
    if (ptr == NULL) {
        return NULL;
    }

    memset(ptr, 0, total_size);

    return ptr;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	struct mem_list* item = mem_list_find(ptr);
	size_t size = item->len;
	mem_list_del(ptr);
	munmap(ptr, size);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if (ptr == NULL) {
        return malloc(size);
    } else if (size == 0) {
        free(ptr);
        return NULL;
    } else {
        struct mem_list *item = mem_list_find(ptr);
        if (item == NULL) {
            return malloc(size);
        } else {
            void *new_ptr = mremap(ptr, item->len, size, MREMAP_MAYMOVE);
            if (new_ptr == MAP_FAILED) {
                new_ptr = malloc(size);
                if (new_ptr == NULL) {
                    return NULL;
                }

                memcpy(new_ptr, ptr, item->len);

                free(ptr);
				mem_list_add(new_ptr, size);
            } else {
                item->start = new_ptr;
                item->len = size;
            }

            return new_ptr;
        }
    }
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
    size_t new_size = nmemb * size;

    if (!ptr) {
        return malloc(new_size);
    }

    struct mem_list *item = mem_list_find(ptr);

    if (!item) {
        return NULL;
    }

    if (!nmemb) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);

    size_t copy_size = (item->len < new_size) ? item->len : new_size;
    memcpy(new_ptr, ptr, copy_size);

    free(ptr);

    return new_ptr;
}
