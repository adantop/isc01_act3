#include "types.h"

PublicKey mk_pub(Seed s);

PrivateKey mk_key(Seed s, PublicKey pub);

int enc(PublicKey k, int m);

int dec(PrivateKey k, int c);

int * encrypt(PublicKey k, char *msg, int size);

char * decrypt(PrivateKey k, int *cypher, int size);

