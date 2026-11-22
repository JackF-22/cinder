CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c11
CPPFLAGS = -Iinclude

TARGET = cinder
SRC = src/runner.c src/assertion.c tests/test_runner.c 

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) include/cinder.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)