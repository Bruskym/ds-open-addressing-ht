#include "prime.h"

static int is_prime(int x){
    if(x < 2) return 0;
    if(x == 2) return 1;
    if(x%2 == 0) return 0;

    for(int i=3; i*i <= x; i+=2){
        if(x % i == 0){
            return 0;
        }
    }
    return 1;
}

int next_prime(int x){
    if(x <= 2) return 2;
    if(x % 2 == 0) x++;

    while(is_prime(x) != 1){
        x+=2;
    }

    return x;
}
