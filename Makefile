CC = gcc
AR = ar
CFLAGS = -std=c11 -Wall -Wextra -I./include
OBJ = $(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))

DEBUG = no
ifeq ($(DEBUG),yes)
  CFLAGS += -O0 -g
else
  CFLAGS += -O3
endif

test: testarkstructs
	./testarkstructs

testarkstructs: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.SECONDEXPANSION:
obj/%.o: src/%.c $$(wildcard include/*.h) $$(wildcard src/*.h)
	$(CC) -o $@ $< $(CFLAGS) -c

.PHONY: clean
clean:
	rm -rf obj/*
	rm -f testarkstructs