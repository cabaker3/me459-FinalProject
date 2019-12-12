# Warnings
WFLAGS	:= -Wall 

# Optimization and architecture
OPT		:= -O3
ARCH   	:= -march=native

# Language standard
CCSTD	:= -std=c99
CXXSTD	:= -std=c++11

# Linker options
LDOPT 	:= $(OPT)
LDFLAGS := 
BIN = "/usr/local/gcc/6.4.0/bin/gcc"
.DEFAULT_GOAL := all

.PHONY: debug
debug : OPT  := -O0 -g -fno-omit-frame-pointer -fsanitize=address
debug : LDFLAGS := -fsanitize=address
debug : ARCH :=
debug : $(EXEC)

all : main

main : main.c merge_ranges.c mamt.c merge_ranges.h mamt.h structs.h structs_def.h task_data.csv
	gcc main.c merge_ranges.c mamt.c $(WFLAGS) $(OPT) -lm -o main

.PHONY: clean
clean:
	rm -f main
