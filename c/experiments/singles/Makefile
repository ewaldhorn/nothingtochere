
CC=clang
CFLAGS=-Wall -g
EXE=memory_usage

all: $(EXE)

%: %.c
  $(CC) $(CFLAGS) $< -o $@

clean:
  rm -rf *.dSYM *.o $(EXE)
