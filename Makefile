TARGET = wave
LIB_NAME = lib$(TARGET).a
LIB_DIR = /usr/local/lib
SRC_DIR = src
TEST_DIR = test
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm

.PHONY: default clean test install uninstall

default: test

OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))
HEADERS = $(wildcard $(SRC_DIR)/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

test: uninstall clean test_
test_: CFLAGS += -D_UNIT_TEST 
test_: $(TARGET)
	./$(TARGET)

clean:
	-rm -f $(SRC_DIR)/*.o
	-rm -f $(TARGET)
	-rm -f *.ppm

install: clean install_
install_: CFLAGS += -O3
install_: src/wave.o
	ar rcs $(LIB_NAME) src/wave.o
	sudo cp $(SRC_DIR)/wave.h /usr/local/include/wave.h
	sudo mv $(LIB_NAME) $(LIB_DIR)/
	
uninstall:
	sudo rm -f /usr/local/lib/$(LIB_NAME)
	sudo rm -f /usr/local/include/wave.h
