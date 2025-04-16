#include <stdio.h>
#include "types.h"
#include "mod.h"

void mod(const bigint val, const bigint base, bigint *quot, bigint *rem, int *err) {
	*err = 0;
	bigint d = val / base;

	if (base == 0) {
		*err = 1;
	} else if (base < 0) {
		*err = 1;
	}

	if (val == 0) {
		*quot = 0;
		*rem = 0;
	} else if (val > 0) {
		*quot = d;
		*rem  = val % base;
	} else {
		if (val - d * base < 0) d--;
		*quot = d;
		*rem = val - d * base;
	}
}

bigint mcd(bigint a, bigint b) {
	int err;
	bigint q;
	bigint r;
	bigint n = (a < b) ? a : b;
	bigint p = (a < b) ? b : a;

	while (1) {
		mod(p, n, &q, &r, &err);
		if (r == 0) break;
		p = n;
		n = r;
	};

	return n;
}

bigint modpow(bigint b, bigint e, bigint m) {
	bigint r = 1;

	while (e > 0) {
		if (e & 1) r = (r * b) % m;
		b = (b * b) % m;
		e >>= 1;
	}

	return r;
}

void print_row(int c, bigint q, bigint r, bigint s, bigint t) {
	printf("| %2d | %5lld | %5lld | %5lld | %5lld |\n", c, q, r, s, t);
}

bigint modinv(bigint b, bigint a, int debug) {
	if (a > b) return 0;

	int r = 0;
	EuclideanArray ao = {0, a, 1, 0};
	EuclideanArray am = {0, b, 0, 1};
	EuclideanArray af = {1, 1, 1, 1};

	if (debug) {
		print_row(r++, ao.q, ao.r, ao.s, ao.t);
		print_row(r++, am.q, am.r, am.s, am.t);
	}

	while (af.r != 0) {
		// Calculate curr
		af.q = ao.r / am.r;
		af.r = ao.r - af.q * am.r;
		af.s = ao.s - af.q * am.s;
		af.t = ao.t - af.q * am.t;
		if (debug) print_row(r++, af.q, af.r, af.s, af.t);

		// Update prev
		if (af.r != 0) {
			ao = am;
			am = af;
		}
	}

	// ax + by = mcd(a, b)
	bigint x = am.s;
	// no queremos x negativos porque causan problemas de
	// portabilidad y seguridad en C
	if (x < 0) x += b;
	if (debug) printf("\nx = %lld, y = %lld\n", x, am.t);
	// are a, b co-primes?
	if (am.r == 1) {
		if (debug) {
			printf("a = %lld, b = %lld son co-primos ya que mcd(%lld, %lld) = %lld\n", a, b, a, b, am.r);
			printf("esto es, x = %lld es el modulo inverso de a = %lld\n", x, a);
		}

		return x;
	} else {
		if (debug) printf("a = %lld, b = %lld no son co-primos ya que mcd(%lld, %lld) = %lld\n", a, b, a, b, am.r);
	}

	return 0;
}

