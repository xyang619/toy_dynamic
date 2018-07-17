#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
    int (*f1ptr)();
    const char* (*f2ptr)();
    void *handle = NULL;
    const char* errmsg = NULL;
    handle = dlopen("libfunc.so", RTLD_LAZY);
    if(!handle)
    {
        fprintf(stderr, "dlopen() %s\n", dlerror());
        exit(1);
    }
    dlerror();
    f1ptr = (int(*)()) dlsym(handle, "func1");
    errmsg = dlerror();
    if(errmsg)
    {
        fprintf(stderr, "dlsysm() for func1 %s\n", errmsg);
        dlclose(handle);
        exit(1);
    }
    f2ptr = (const char* (*)())dlsym(handle, "func2");
    errmsg = dlerror();
    if(errmsg)
    {
        fprintf(stderr, "dlsym() for func2 %s\n", errmsg);
        dlclose(handle);
        exit(1);
    }
    printf("func1: %d\n", (*f1ptr)());
    printf("func2: %s\n", (*f2ptr)());
    dlclose(handle);
    handle = dlopen("libplugin.so", RTLD_LAZY);
    if(!handle)
    {
        fprintf(stderr, "dlopen() %s\n", dlerror());
        exit(1);
    }
    void (*f3ptr)(int);
    f3ptr = (void (*)(int)) dlsym(handle, "func3");
    errmsg = dlerror();
    if(errmsg)
    {
        fprintf(stderr, "dlsym() for func3 %s\n", errmsg);
        dlclose(handle);
        exit(1);
    }
    f3ptr(1);
    f3ptr(100);
    dlclose(handle);
    return 0;
}

