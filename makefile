CC = gcc
CFLAGS = -Wall -O3 -fPIC
DEPS = api.h

all: libfunc libplugin main

libfunc: func1.o func2.o
	$(CC) $(CFLAGS) -shared -o libfunc.so func1.o func2.o

libplugin: func3.o libfunc
	$(CC) $(CFLAGS) -shared -o libplugin.so func3.o -L. -lfunc

main: main.o
	$(CC) $(CFLAGS) -ldl -o main main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o libfunc.so libplugin.so main

