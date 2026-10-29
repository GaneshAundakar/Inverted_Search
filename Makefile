.PHONY: all clean

var := $(patsubst %.c, %.o, $(wildcard *.c))

all: invert.exe

invert.exe: $(var)
	gcc -o $@ $^

clean:
	rm -f *.exe *.o
