#include <stdio.h>
#include <stdlib.h>
#include "sieve.h"

int main()
{
    unsigned int target;
    printf("Input nth prime number you want to find: ");
    if (scanf("%d", &target) != 1)
    {
        abort();
    }
    struct sieve_t s = init_sieve(target);
    fill_sieve(&s);
    printf("%d prime number: ", target);
    // search prime target number
    for (unsigned long long i = 0; i < __LONG_LONG_MAX__; i++)
    {
        if (is_prime(&s, i))
        {
            target--;
            if (target == 0)
            {
                printf("%llu\n", i);
                break;
            }
        }
    }
    free_sieve(&s);
}