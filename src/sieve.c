#include "sieve.h"

int is_prime(struct sieve_t *sv, unsigned n)
{
    if (n < 2)
    {
        return 0;
    }
    if (n == 2 || n == 3)
    {
        return 1;
    }
    if (n % STEP == 5)
    {
        return !((sv->mod5[n / (STEP * __CHAR_BIT__)] >> ((n / STEP) % __CHAR_BIT__)) & 1u);
    }
    if (n % STEP == 1)
    {
        return !((sv->mod1[n / (STEP * __CHAR_BIT__)] >> ((n / STEP) % __CHAR_BIT__)) & 1u);
    }
    return 0;
}

void fill_sieve(struct sieve_t *sv)
{
    sv->mod1[0] = 1u;
    for (unsigned i = 5; i * i <= sv->n * __CHAR_BIT__ * STEP; i += STEP)
    {
        for (int y = i; y <= i + 2; y += 2)
        {
            if (y * y > sv->n * __CHAR_BIT__ * STEP)
            {
                break;
            }
            if (is_prime(sv, y))
            {
                for (unsigned j = y * y; j < sv->n * __CHAR_BIT__ * STEP; j += y)
                {
                    if (j % STEP == 5)
                    {
                        sv->mod5[j / (STEP * __CHAR_BIT__)] |= 1u << ((j / STEP) % __CHAR_BIT__);
                    }
                    else if (j % STEP == 1)
                    {
                        sv->mod1[j / (STEP * __CHAR_BIT__)] |= 1u << ((j / STEP) % __CHAR_BIT__);
                    }
                }
            }
        }
    }
}

struct sieve_t init_sieve(unsigned int target)
{
    struct sieve_t s;
    unsigned int size = ((target * log(target * log(target))) / 48) + 1; // size in bytes
    s.n = size;
    s.mod1 = (unsigned char *)calloc(s.n, sizeof(unsigned char));
    s.mod5 = (unsigned char *)calloc(s.n, sizeof(unsigned char));
    return s;
}

void free_sieve(struct sieve_t *s)
{
    free(s->mod1);
    s->mod1 = 0;
    free(s->mod5);
    s->mod5 = 0;
    s->n = 0;
}