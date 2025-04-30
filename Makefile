CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iincludes
TARGET = app

SRC = src/app.c src/hash_table.c src/utils/prime.c
HEADERS = includes/ht_structure.h includes/prime.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)