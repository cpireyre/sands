CFLAGS:=-I/opt/homebrew/Cellar/raylib/5.0/include -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib
CFLAGS+= -Wall -Wextra -Werror -pedantic

.PHONY: sands
sands: sands.c
	clang $(CFLAGS) $^ -o $@
	./$@
