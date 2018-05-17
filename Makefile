# This should point wherever libyaml is installed.
PREFIX=${HOME}/.local
CFLAGS=-I$(INC) -L$(LIB) 
INC=$(YAMLSRC)
LIB=$(YAMLSRC)
INC=$(PREFIX)/include
LIB=$(PREFIX)/lib

.PHONY: all clean

all: yaml-test.out

%.out: %.cpp 
	g++ $^ $(CFLAGS) -lyaml -o $@

clean:
	rm -f *.out
