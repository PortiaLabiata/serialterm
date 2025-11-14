CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -g
SRCS := main.c ui.c strbuf.c
EXEC := st

OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: $(EXEC)
	echo 'Done'

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -lncurses -o $(EXEC) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(EXEC)
