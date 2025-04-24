#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "crypto.h"

void gen_keys(int p, int q);

PublicKey read_public_key(char *filename);

PrivateKey read_private_key(char *filename);

void write_data(char *filename, int count, int *crypt);

int * read_data(char *filename, int *count);

void print_help(char *cmd);

int main(int argc, char *argv[argc]) {
	if (argc != 4) {
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "genkeys") == 0) {
		int p = atoi(argv[2]);
		int q = atoi(argv[3]);
		if (p * q < 127) {
			fprintf(stderr, "p * q should be larger than 128\n");
			return EXIT_FAILURE;
		}

		gen_keys(p, q);
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[1], "encrypt") == 0) {
		PublicKey pub = read_public_key(argv[2]);
		int size = strlen(argv[3]);
		int *c = encrypt(pub, argv[3], size);

		// print the output
		printf("[");
		for (int i = 0; i < size - 1; i++) printf("%x, ", c[i]);
		printf("%x]\n", c[size - 1]);

		// Save the file
		write_data("encrypted.bin", size, c);
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[1], "decrypt") == 0) {
		PrivateKey priv = read_private_key(argv[2]);
		int size;
		int *c = read_data(argv[3], &size);
		
		char *msg = decrypt(priv, c, size);
		
		printf("message: %s\n", msg);
	} else {
		fprintf(stderr, "invalid command\n");
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


void gen_keys(int p, int q) {
	// Cualquier combinacion de numeros primos cuya multiplicacion
	// sea mayor que el numero de caracteres 128
	// Seed s = {22531, 72997};
	// Seed s = {2, 71};
	Seed s = {p, q};
	PublicKey  pub  = mk_pub(s);
	PrivateKey priv = mk_key(s, pub);

	FILE *fp = fopen("key", "w");
	if (!fp) {
		perror("could not write private key");
		return;
	}
	fprintf(fp, "%lld %lld\n", priv.d, priv.n);
	fclose(fp);

	fp = fopen("key.pub", "w");
	if (!fp) {
		perror("could not write public key");
		return;
	}
	fprintf(fp, "%lld %lld\n", pub.e, pub.n);
	fclose(fp);
}


PublicKey read_public_key(char *filename) {
	PublicKey *pub = malloc(sizeof(PublicKey));

	FILE  *fp = fopen(filename, "r");
	if (!fp) {
		perror("could not read public key");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%lld %lld", &pub->e, &pub->n);
	fclose(fp);
	return *pub;
}


PrivateKey read_private_key(char *filename) {
	PrivateKey *priv = malloc(sizeof(PrivateKey));

	FILE  *fp = fopen(filename, "r");
	if (!fp) {
		perror("could not private public key");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%lld %lld", &priv->d, &priv->n);
	fclose(fp);
	return *priv;
}


void write_data(char *filename, int count, int *crypt) {
	FILE *fp = fopen(filename, "wb");
	if (!fp) {
		perror("could not save message");
		exit(EXIT_FAILURE);
	}

	fwrite(crypt, sizeof(int), count, fp);
	fclose(fp);
}


int * read_data(char *filename, int *count) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		perror("could not open encrypted message file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	*count = size / sizeof(int);

	int *data = malloc(size);
	if (!data) {
		perror("could not load data");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	int read = fread(data, sizeof(int), *count, fp);
	fclose(fp);

	if (read != *count) {
		fprintf(stderr, "read mismatch: expected %d, got %d\n", *count, read);
		exit(EXIT_FAILURE);
	}

	return data;
}


void print_help(char *cmd) {
	printf("usage: %s command args\n\n", cmd);
	printf("commands:\n\n");
	printf("    genkeys\n");
	printf("      args: p q\n");
	printf("      example: %s genkeys 2 71\n\n", cmd);
	printf("    encrypt\n");
	printf("      args: pubkey message\n");
	printf("      example: %s encrypt key.pub \"hello world!\"\n\n", cmd);
	printf("    decrypt\n");
	printf("      args: privkey file\n");
	printf("      example: %s decrypt key encrypted.bin\n", cmd);
}

