#include "types.h"

PrivateKey mk_key(Seed s);

PublicKey mk_pub(PrivateKey p);

int enc(PrivateKey k, int m);

int dec(PublicKey k, int c);

int * encrypt(PrivateKey k, char *msg, int size);

char * decrypt(PublicKey k, int *cypher, int size);

