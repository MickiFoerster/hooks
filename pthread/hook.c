#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <bits/pthreadtypes.h>
#include <dlfcn.h>

void store_id(pthread_t  * id) {
    fprintf(stderr, "[HOOK]: new thread created with id  0x%lx\n", (*id));
}

#undef pthread_create

int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start)(void *), void * arg)
{
    int rc;
    static int (*real_create)(pthread_t * , pthread_attr_t *, void * (*start)(void *), void *) = NULL;
    if (!real_create)
        real_create = dlsym(RTLD_NEXT, "pthread_create");

    rc = real_create(thread, attr, start, arg);
    if(!rc) {
        store_id(thread);
    }
    return rc;
}

#undef pthread_create
void log_pthread_join(pthread_t thread) {
    fprintf(stderr, "[HOOK]: thread 0x%lx joined \n", thread);
}

int pthread_join(pthread_t thread, void **retval) 
{
    int rc;
    static int (*real_join)(pthread_t thread, void **retval) = NULL;
    if (!real_join)
        real_join = dlsym(RTLD_NEXT, "pthread_join");

    rc = real_join(thread, retval);
    if (!rc) {
        log_pthread_join(thread);
    }

    return rc;
}

