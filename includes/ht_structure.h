#ifndef HT_STRUCTURE_H
#define HT_STRUCTURE_H

#define PRIME_1 173
#define PRIME_2 179
#define HT_INITIAL_SIZE 53

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int count;
    int base_size;
    int size;
    ht_item** items;
} hash_table;

hash_table* new_ht();
void delete_hash_table(hash_table* ht_ptr);

char* search(hash_table* ht, char* key);
void insert(hash_table* ht, char* key, char* value);
void delete(hash_table* ht, char* key);

#endif