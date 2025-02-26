#ifndef SIEVE_H
#define SIEVE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STEP 6

struct sieve_t
{
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};

int is_prime(struct sieve_t *sv, unsigned n);
void fill_sieve(struct sieve_t *sv);
struct sieve_t init_sieve(unsigned int target);
void free_sieve(struct sieve_t *s);

#endif