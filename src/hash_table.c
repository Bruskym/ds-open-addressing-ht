#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ht_structure.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(char* k, char* v){
    ht_item* ht_item_ptr = malloc(sizeof(ht_item));

    if (ht_item_ptr == NULL) {
        fprintf(stderr, "Error allocating memory for hashtable item.");
        exit(1);
    }

    ht_item_ptr->key = strdup(k);
    ht_item_ptr->value = strdup(v);

    return ht_item_ptr;
}

static void ht_delete_item(ht_item* item){
    free(item->key);
    free(item->value);
    free(item);
}

static hash_table* create_ht(int ht_size){
    hash_table* ht = malloc(sizeof(hash_table));

    if (ht == NULL) {
        fprintf(stderr, "Error allocating memory for hashtable.");
        exit(1);
    }

    ht->base_size = ht_size;

    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc(ht->size, sizeof(ht_item*));
    if (ht->items == NULL) {
        fprintf(stderr, "Error allocating memory for hashtable items.");
        free(ht);
        exit(1);
    }

    return ht;
}

hash_table* new_ht(){
    return create_ht(HT_INITIAL_SIZE);
}

void delete_hash_table(hash_table* ht_ptr){ 
    for(int i=0; i<ht_ptr->size; i++){
        ht_item* item = ht_ptr->items[i];
        if(item != NULL && item != &HT_DELETED_ITEM){
            ht_delete_item(item);
        }
    }
    free(ht_ptr->items);
    free(ht_ptr);
}

static void resize_ht(hash_table* ht_ptr, int new_size){ 
    if(new_size < HT_INITIAL_SIZE) return;

    hash_table* new_ht = create_ht(new_size);

    for(int i=0; i<ht_ptr->size; i++){
        ht_item* old_ht_item = ht_ptr->items[i];
        if(old_ht_item != NULL && old_ht_item != &HT_DELETED_ITEM){
            insert(new_ht, old_ht_item->key, old_ht_item->value);
        }
    }

    ht_ptr->base_size = new_ht->base_size;
    ht_ptr->count = new_ht->count;
    ht_ptr->size = new_ht->size;

    ht_item** temp_items = new_ht->items;
    new_ht->items = ht_ptr->items;
    ht_ptr->items = temp_items;

    delete_hash_table(new_ht);
}

static void resize_up(hash_table* ht_ptr){
    resize_ht(ht_ptr, ht_ptr->base_size*2);
}

static void resize_down(hash_table* ht_ptr){
    resize_ht(ht_ptr, ht_ptr->base_size/2);
}

static int ht_hash_function(char* s, int size, const int salt){
    int hash = 0;
    const int len_s = strlen(s);

    for(int i=0; i<len_s; i++){
        hash = (hash * salt + s[i]) % size;
    }

    return hash;
}

static int get_hash(char* s, const int num_buckets, const int attempt){
    const int hash_a = ht_hash_function(s, num_buckets, PRIME_1);
    int hash_b = ht_hash_function(s, num_buckets, PRIME_2);
    
    if (hash_b == (num_buckets - 1)){
        hash_b = 1;
    }

    return (hash_a + (attempt * (hash_b+1))) % num_buckets;  
}

char* search(hash_table* ht, char* key){
    int i = 1;
    int hash = get_hash(key, ht->size, 0);
    ht_item* item = ht->items[hash];

    while (item != NULL){

        if(item != &HT_DELETED_ITEM && (strcmp(item->key, key) == 0)){
            return item->value;
        }

        hash = get_hash(key, ht->size, i);
        item = ht->items[hash];
        i++;
    }
    
    return NULL;
}

void insert(hash_table* ht, char* key, char* value){
    int i = 1;
    int hash = get_hash(key, ht->size, 0);
    ht_item* item = ht->items[hash];

    while (1){

        if(item == NULL || item == &HT_DELETED_ITEM){
            ht->items[hash] = ht_new_item(key, value);
            ht->count++;
            
            if((float)ht->count/ht->size > 0.7){
                resize_up(ht);
            }

            return;
        }

        if(strcmp(item->key, key) == 0){
            free(item->value);
            item->value = strdup(value);
            return;
        }

        hash = get_hash(key, ht->size, i);
        item = ht->items[hash];
        i++;
    }
}

void delete(hash_table* ht, char* key){
    int i = 1;
    int hash = get_hash(key, ht->size, 0);
    ht_item* item = ht->items[hash];

    while(item != NULL){
        
        if(strcmp(item->key, key) == 0){
            ht_delete_item(item);
            ht->items[hash] = &HT_DELETED_ITEM;
            ht->count--;
            
            if((float)ht->count/ht->size < 0.1){
                resize_down(ht);
            }

            return;
        }

        hash = get_hash(key, ht->size, i);
        item = ht->items[hash];
        i++;
    }
}
