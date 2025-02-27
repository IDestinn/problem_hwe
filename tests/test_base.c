#include "test_base.h"

void test_primes(unsigned int target, unsigned long long expected_result)
{
    struct sieve_t s = init_sieve(target);
    fill_sieve(&s);
    // search prime target number
    unsigned int tmp_target = target;
    for (unsigned long long i = 0; i < __LONG_LONG_MAX__; i++)
    {
        if (is_prime(&s, i))
        {
            tmp_target--;
            if (tmp_target == 0)
            {
                if (i != expected_result)
                {
                    fprintf(stderr, "%dth number is %llu, but expected %llu\n", target, i, expected_result);
                    free_sieve(&s);
                    abort();
                }
                else
                {
                    return;
                };
            }
        }
    }
    free_sieve(&s);
}