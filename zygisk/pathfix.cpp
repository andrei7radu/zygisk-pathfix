#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define OLD_PKG "io.github.huskydg.magisk"
#define NEW_PKG "io.github.x0eg0.magisk"

static int (*orig_stat)(const char *path, struct stat *buf);
static int (*orig_access)(const char *path, int mode);
static int (*orig_open)(const char *path, int flags, ...);

void rewrite_path(const char *in, char *out, size_t size) {
    snprintf(out, size, "%s", in);
    char *pos = strstr(out, OLD_PKG);
    if (pos) {
        memcpy(pos, NEW_PKG, strlen(NEW_PKG));
    }
}

int my_stat(const char *path, struct stat *buf) {
    if (path && strstr(path, OLD_PKG)) {
        char new_path[512];
        rewrite_path(path, new_path, sizeof(new_path));
        return orig_stat(new_path, buf);
    }
    return orig_stat(path, buf);
}

int my_access(const char *path, int mode) {
    if (path && strstr(path, OLD_PKG)) {
        char new_path[512];
        rewrite_path(path, new_path, sizeof(new_path));
        return orig_access(new_path, mode);
    }
    return orig_access(path, mode);
}

int my_open(const char *path, int flags, ...) {
    if (path && strstr(path, OLD_PKG)) {
        char new_path[512];
        rewrite_path(path, new_path, sizeof(new_path));
        return orig_open(new_path, flags);
    }
    return orig_open(path, flags);
}

__attribute__((constructor))
void init() {
    void *libc = dlopen("libc.so", RTLD_NOW);

    orig_stat = (int (*)(const char *, struct stat *)) dlsym(libc, "stat");
    orig_access = (int (*)(const char *, int)) dlsym(libc, "access");
    orig_open = (int (*)(const char *, int, ...)) dlsym(libc, "open");
}
