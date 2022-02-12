#include <openssl/sha.h>        //Required for SHA256 (gcc -lssl -lcrypto)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char extern global_checksum[100];

void calcSHA256 (const char *input) {
    char temp[100];

    unsigned char *d = SHA256(input, strlen(input), 0); //Generate SHA256SUM of input

    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(temp, "%02x", d[i]);
        strcat(global_checksum, temp); //Load SHA256_DIGEST_LENGTH into global checksum variable
    }
}
