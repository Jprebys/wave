TARGET = wave
LIB_NAME = lib$(TARGET).a
LIB_DIR = /usr/local/lib
SRC_DIR = src
TEST_DIR = test
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm

.PHONY: default all clean debug test install uninstall

default: test
all: default

debug: CFLAGS += -g
debug: default


OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))
HEADERS = $(wildcard $(SRC_DIR)/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

test: CFLAGS += -D_UNIT_TEST 
test: $(TARGET)
	./$(TARGET)

clean:
	-rm -f $(SRC_DIR)/*.o
	-rm -f $(TARGET)
	-rm -f *.ppm

install: all
	cp $(TARGET) /usr/local/lib/libwave.a
	
uninstall:
	rm -f /usr/local/bin/$(TARGET)
