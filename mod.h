#include "types.h"

int isprime(bigint val);

void mod(bigint val, bigint base, bigint *quot, bigint *rem, int *err);

bigint mcd(bigint a, bigint b);

bigint modpow(bigint b, bigint e, bigint m);

void print_row(int c, bigint q, bigint r, bigint s, bigint t);

bigint modinv(bigint b, bigint a, int debug);

