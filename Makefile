LDLIBS=-lncurses
LDFLAG=

CFLAGS=-Wall -Werror -O3 -g
CC=gcc

SRC=$(shell find . -name "*.c")
INCLUDE=include

TARGET=spacegame

all: clean $(TARGET) run

$(TARGET): $(SRC)
	$(CC) -I $(INCLUDE) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS)

debug: $(TARGET)
	ulimit -c unlimited

install:
	sudo cp $(TARGET) /usr/local/bin/$(TARGET)

update: clean all 

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
