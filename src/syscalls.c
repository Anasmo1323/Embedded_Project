//
// Created by Anas Mohamed on 6/3/2025.
//
#include <errno.h>
#include <sys/types.h>

caddr_t _sbrk(int incr) {
    errno = ENOMEM; // No memory available
    return (caddr_t)-1; // Return error
}