CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -MMD -MP

SRC = $(shell find src -name '*.c')
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

roguer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: roguer
	./roguer

clean:
	rm -rf build roguer

.PHONY: run clean

-include $(DEP)
