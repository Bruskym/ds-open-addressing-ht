#include<stdio.h>
#include<stdlib.h>

#include "ht_structure.h"

int main(){
    hash_table* ht = new_ht();
    insert(ht, "name", "Alice");
    insert(ht, "job", "Engineer");

    char* value = search(ht, "name");
    printf("Name: %s\n", value);

    delete(ht, "job");
    delete_hash_table(ht);
}