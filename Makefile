CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
SRC = morse.c
TARGET = morse

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)