#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "crypto.h"

int main(int argc, char *argv[argc]) {
	// Cualquier combinacion de numeros primos cuya multiplicacion
	// sea mayor que el numero de caracteres 128
	Seed s = {2, 71};
	PrivateKey priv = mk_key(s);
	PublicKey  pub  = mk_pub(priv);

	printf("PrivateKey<e=%lld, n=%lld>\n", priv.e, priv.n);
	printf("PublicKey<d=%lld, n=%lld>\n", pub.d, pub.n);

	char *m = "hello";
	if (argc == 2) m = argv[1];
	int size = strlen(m);
	printf("Message size: %d\n", size);
	int  *c = encrypt(priv, m, size);
	char *n = decrypt(pub, c, size);

	printf("\"%s\" --> \"", m);
	for (int i = 0; i < size; i++) printf("%c", c[i]);
	printf("\" [");
	for (int i = 0; i < size - 1; i++) printf("%d, ", c[i]);
	printf("%d] --> \"%s\"\n", c[size - 1], n);
	
	return EXIT_SUCCESS;
}
