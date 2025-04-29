CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = app

SRC = app.c hash_table.c utils/prime.c
HEADERS = ht_structure.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)