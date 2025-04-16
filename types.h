#ifndef TYPES_H
#define TYPES_H

typedef long long bigint;

typedef struct {
	bigint q;
	bigint r;
	bigint s;
	bigint t;
} EuclideanArray;

typedef struct {
	bigint p;
	bigint q;
} Seed;

typedef struct {
	bigint e;
	bigint d;
	bigint n;
} PrivateKey;

typedef struct {
	bigint d;
	bigint n;
} PublicKey;

#endif
