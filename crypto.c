#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "mod.h"

PrivateKey mk_key(Seed s, PublicKey pub) {
	PrivateKey p;
	p.n = pub.n;
	bigint phi = (s.p - 1) * (s.q - 1);

	p.d = modinv(phi, pub.e, 0);

	return p;
}

PublicKey mk_pub(Seed s) {
	if (!isprime(s.p)) {
		fprintf(stderr, "error: P is not prime\n");
		exit(1);
	}

	if (!isprime(s.q)) {
		fprintf(stderr, "error: Q is not prime\n");
		exit(1);
	}

	PublicKey pub;
	bigint phi = (s.p - 1) * (s.q - 1);
	pub.e = 0;
	pub.n = s.p * s.q;

	for (bigint i = 2; i <= phi; i++) {
		bigint cd = mcd(i, phi);
		if (cd == 1) {
			pub.e = i;
			break;
		}
	}

	return pub;
}

int enc(PublicKey k, int m) {
	return modpow(m, k.e, k.n);
}

int dec(PrivateKey k, int c) {
	return modpow(c, k.d, k.n);
}

int * encrypt(PublicKey k, char *msg, int size) {
	int *c = malloc(size * sizeof(int));
	if (!c) {
		perror("malloc failed");
		exit(1);
	}

	for (int i = 0; i < size; i++) c[i] = (int)enc(k, (int)msg[i]);

	return c;
}

char * decrypt(PrivateKey k, int *cypher, int size) {
	char *m = malloc((size + 1) * sizeof(char));
	if (!m) {
		perror("malloc failed");
		exit(1);
	}

	for (int i = 0; i < size; i++) m[i] = (char)dec(k, cypher[i]);
	m[size] = '\0';

	return m;
}

