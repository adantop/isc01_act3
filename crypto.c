#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "mod.h"

PrivateKey mk_key(Seed s) {
	PrivateKey p;
	bigint phi = (s.p - 1) * (s.q - 1);
	p.e = 0;
	p.n = s.p * s.q;

	//TODO phi must be prime
	for (bigint i = 2; i <= phi; i++) {
		bigint cd = mcd(i, phi);
		if (cd == 1) {
			p.e = i;
			break;
		}
	}

	p.d = modinv(phi, p.e, 0);

	return p;
}

PublicKey mk_pub(PrivateKey p) {
	PublicKey pub = {p.d, p.n};
	return pub;
}

int enc(PrivateKey k, int m) {
	return modpow(m, k.e, k.n);
}

int dec(PublicKey k, int c) {
	return modpow(c, k.d, k.n);
}

int * encrypt(PrivateKey k, char *msg, int size) {
	int *c = malloc(size * sizeof(int));
	if (!c) {
		perror("malloc failed");
		exit(1);
	}

	for (int i = 0; i < size; i++) c[i] = (int)enc(k, (int)msg[i]);

	return c;
}

char * decrypt(PublicKey k, int *cypher, int size) {
	char *m = malloc((size + 1) * sizeof(char));
	if (!m) {
		perror("malloc failed");
		exit(1);
	}

	for (int i = 0; i < size; i++) m[i] = (char)dec(k, cypher[i]);
	m[size] = '\0';

	return m;
}

