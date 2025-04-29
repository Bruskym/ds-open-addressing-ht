# C Hash Table

A resizable hash table implementation in C using open addressing with double hashing.

## Features

- Dynamic resizing (up/down)
- Open addressing with double hashing
- Prime-sized bucket arrays to reduce collisions
- Lazy deletion using sentinel items
- Simple memory-safe API

## Example Usage

```bash
hash_table* ht = new_ht();
insert(ht, "name", "Alice");
insert(ht, "job", "Engineer");

char* value = search(ht, "name");
printf("Name: %s\n", value);

delete(ht, "job");
delete_hash_table(ht);
```

## Build

```bash
make
./app
```
