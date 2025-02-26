#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/sieve.h"

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

struct test_case_t
{
    unsigned int target;
    unsigned long long expected_result;
};

int main()
{
    struct test_case_t tests[] = {
        {10, 29},
        {20, 71},
        {50, 229},
        {1000000, 15485863}};

    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        test_primes(tests[i].target, tests[i].expected_result);
    }
    printf("All tests passed!\n");
    return 0;
}