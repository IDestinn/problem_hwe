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

int main()
{
    unsigned cnt = 0, target = 20;
    struct sieve_t s;
    s.n = 16;
    s.mod1 = (unsigned char *)calloc(s.n, sizeof(unsigned char));
    s.mod5 = (unsigned char *)calloc(s.n, sizeof(unsigned char));
    fill_sieve(&s);
    printf("m1 m5\n");
    for (int i = 0; i < s.n; i++)
    {
        printf("%x %x\n", s.mod1[i], s.mod5[i]);
    }
    for (int i = 0; i < 1000; i++)
    {
        if (is_prime(&s, i))
        {
            printf("%d, ", i);
        }
    }
    printf("\n");
    free(s.mod1);
    free(s.mod5);
}