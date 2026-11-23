CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c11
CPPFLAGS = -Iinclude

TARGET = cinder
SRC = src/runner.c src/assertion.c tests/test_runner.c 

.PHONY: all run clean test

all: $(TARGET)

$(TARGET): $(SRC) include/cinder.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f run_tests

run_tests: src/runner.c src/assertion.c $(TARGET) tests/*.c
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runner.c src/assertion.c tests/*.c -o run_tests

test: run_tests
	./run_tests