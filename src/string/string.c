/* SPDX-License-Identifier: BSD-3-Clause */

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	char *dest = destination;

	while (*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	char* dest = destination;
	size_t i;
	for (i = 0; i < len && *source != '\0'; i++) {
		*dest = *source;
		dest++;
		source++;
	}

	for (; i < len; i++) {
		*dest = '\0';
		dest++;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	char *dest = destination;
	while (*dest != '\0') {
		dest++;
	}

	while (*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	char *dest = destination;
	while (*dest != '\0') {
		dest++;
	}

	for (size_t i = 0; i < len && *source != '\0'; i++) {
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	while (*str1 != '\0' || *str2 != '\0') {
        if (*str1 != *str2) {
            return (*str1 < *str2) ? -1 : 1;
        }
        str1++;
        str2++;
    }
    return 0;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	for (size_t i = 0; i < len && (*str1 != '\0' || *str2 != '\0'); i++) {
        if (*str1 != *str2) {
            return (*str1 < *str2) ? -1 : 1;
        }
        str1++;
        str2++;
    }
    return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	while (*str != '\0') {
		if (*str == c)
			return (char*) str;
		str++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	char *result = NULL;

    while (*str != '\0') {
        if (*str == c) {
            result = (char *) str;
        }
        str++;
    }

	return result;
}

char *strstr(const char *str1, const char *str2)
{
	/* TODO: Implement strstr(). */
	if (*str2 == '\0') {
        return (char *) str1;
    }

    while (*str1 != '\0') {
        if (*str1 == *str2) {
            const char *p1 = str1;
            const char *p2 = str2;

            while (*p1 == *p2 && *p2 != '\0') {
                p1++;
                p2++;
            }

            if (*p2 == '\0') {
                return (char *) str1;
            }
        }
        str1++;
    }

	return NULL;
}

char *strrstr(const char *str1, const char *str2)
{
	/* TODO: Implement strrstr(). */
	if (*str2 == '\0') {
        return (char *) str1;
    }

    size_t needle_len = strlen(str2);
    char *last_occurrence = NULL;

    while ((str1 = strstr(str1, str2)) != NULL) {
        last_occurrence = (char *) str1;
        str1 += needle_len;
    }

    return last_occurrence;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	char *dest = (char *) destination;
    const char *src = (const char *) source;

    for (size_t i = 0; i < num; i++) {
        dest[i] = src[i];
    }

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	char *dest = (char *) destination;
    const char *src = (const char *) source;

    if (dest <= src) {
        for (size_t i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = num; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    }
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	const unsigned char *p1 = (const unsigned char *) ptr1;
    const unsigned char *p2 = (const unsigned char *) ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }

    return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	char *source_ptr = (char *) source;

    for (size_t i = 0; i < num; i++) {
        source_ptr[i] = (char) value;
    }

    return source;
}
