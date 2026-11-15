#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

static char *base_path;

static void free_base_path(void)
{
    SDL_free(base_path);
}

const char *dd_base_path(void)
{
    if (!base_path) {
        base_path = SDL_GetBasePath();
        if (base_path) atexit(free_base_path);
    }
    return base_path;
}

Uint64 dd_ticks_ns(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (Uint64)now.tv_sec * 1000000000 + now.tv_nsec;
}
