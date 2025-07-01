/*
 * Copyright (C) 2014
 *
 * Simple openssl example (AES)
 *
 */

//sudo apt-get install libimobiledevice-dev libplist-dev libusbmuxd-dev libssl-dev

#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// ...

int main(int argc, char *argv[])
{
	/*------------------INIT DATA------------------*/

	unsigned char *input_string = "Hello world!";

	unsigned int message_len = strlen(input_string) + 1;
	unsigned encrypt_len = (message_len % AES_BLOCK_SIZE == 0) ? 
				message_len : 
				(message_len / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	
	const unsigned int KEY_SIZE = 128;
	//const unsigned int KEY_BYTE_SIZE = KEY_SIZE / 8;
	unsigned char key[] = {0x00, 0x01, 0x02, 0x03,
			       0x04, 0x05, 0x06, 0x07,
			       0x08, 0x09, 0x0a, 0x0b,
			       0x0c, 0x0d, 0x0e, 0x0f}; // KEY_BYTE_SIZE == 16
	AES_KEY aes_enc, aes_dec;
	int ret = -1; 
	
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0, AES_BLOCK_SIZE);

	unsigned char *encrypt_string = malloc(message_len * sizeof(char));
	memset(encrypt_string, '\0', message_len);
    	
	unsigned char *decrypt_string = malloc(message_len * sizeof(char));
	memset(decrypt_string, '\0', message_len);
	
	printf("\ninput_string size =  %d", strlen(input_string));	
	printf("\nAES_BLOCK_SIZE =  %d", AES_BLOCK_SIZE);
	printf("\nencrypt_len =  %d", encrypt_len);

	/*------------------ENCRYPT------------------*/

	/*AES_set_encrypt_key(key1, 128, &enc_key);
    	AES_encrypt(text, enc_out, &enc_key);*/
	if(ret = AES_set_encrypt_key(key, KEY_SIZE, &aes_enc) < 0)
		return 1;
	memset(iv, 0, AES_BLOCK_SIZE);
	AES_cbc_encrypt(input_string, encrypt_string, encrypt_len, &aes_enc, iv, AES_ENCRYPT);

	/*------------------DECRYPT------------------*/

	/*AES_set_decrypt_key(key1,128,&dec_key);
    	AES_decrypt(enc_out, dec_out, &dec_key);*/
	if(ret = AES_set_decrypt_key(key, KEY_SIZE, &aes_dec) < 0)
		return 1;
	memset(iv, 0, AES_BLOCK_SIZE);
	AES_cbc_encrypt(encrypt_string, decrypt_string, encrypt_len, &aes_dec, iv, AES_DECRYPT);

	/*------------------PRINT RESULTS------------------*/

	printf("\nString = %s\n", input_string);
	for(int i = 0; i < message_len; i++)
        	printf("%02X", (unsigned int)input_string[i]);
	printf("\n");
	
	printf("\nEncString = %s\n", encrypt_string);
	for(int i = 0; i < message_len; i++)
        	printf("%02X", (unsigned int)encrypt_string[i]);
	printf("\n");

	printf("\nDecString = %s\n", decrypt_string);
	for(int i = 0; i < message_len; i++)
        	printf("%02X", (unsigned int)decrypt_string[i]);
	printf("\n\n");

	if(strcmp(input_string, decrypt_string) < 0)
		printf("\nError!\n\n");
	else
		printf("\nGood.\n\n");

	/*------------------DEINIT DATA------------------*/

	free(encrypt_string);
    	free(decrypt_string);

	/*---------------------------------------------*/

	return 0;
}

