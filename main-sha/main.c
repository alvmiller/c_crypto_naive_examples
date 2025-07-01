/*
 * Copyright (C) 2014
 *
 * Simple openssl example (SHA)
 *
 */

//sudo apt-get install libimobiledevice-dev libplist-dev libusbmuxd-dev libssl-dev

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void printSHAX(unsigned char * (*func_ptr)(const unsigned char *d, unsigned long n, unsigned char *md),
	       const char *message,
	       size_t SHAX_DIGEST_LENGTH)
{
	//char message[] = "123";
	//printf("SHAX digest: %s\n", message);	
	//printf("SHAX digest: %s\n", (unsigned char *)&message); 
	// (unsigned char *)&message - if Local - good, if no local - bad

	unsigned char digest[SHAX_DIGEST_LENGTH];
    
    	func_ptr((unsigned char *)message, strlen(message), (unsigned char *)digest);    

    	char mdString[SHAX_DIGEST_LENGTH * 2 + 1];

    	for(int i = 0; i < SHAX_DIGEST_LENGTH; i++)
        	sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

    	printf("SHAX digest: %s |  %s\n", mdString, digest);
}

int main(int argc, char *argv[])
{
	char message[] = "123";

	printSHAX(SHA1, message, SHA_DIGEST_LENGTH);
	printSHAX(SHA256, message, SHA256_DIGEST_LENGTH);

	return 0;
}

