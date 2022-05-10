/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 
 * Student Email: 
 * ---------------------------------
 */
#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define A 65
# define Z 91
# define a 97
# define z 122

char* encrypt(char *plaintext, int key) {

	int i = 0;
	char *cipher;
//	int len = z - a;
//	int counter = 0;
	cipher = (char*) malloc(strlen(plaintext) * sizeof(char));

//	for (i = 0; i < strlen(plaintext); i++) {
	while (i != strlen(plaintext)) {

		if (isalpha(plaintext[i]) && isupper(plaintext[i])
				&& plaintext[i] != '\0') {
			cipher[i] = plaintext[i] + key;
		} else if (isalpha(plaintext[i]) && islower(plaintext[i])
				&& plaintext[i] != '\0') {
			if ((plaintext[i]) > (z - key)) {
				cipher[i] = plaintext[i] - (26 - key);
			} else
				cipher[i] = ((int) plaintext[i]) + key;

		} else {
//			counter++;
//			printf("Counter %d", counter);
			cipher[i] = plaintext[i];
		}
		i++;

//		for (i = 0; i < strlen(plaintext); i++) {
//		}
//		if ((i + key) > z) {
//			cipher = tolower((i + key) - 26);
//		} else
//			cipher = tolower(i + key);
//		crypt[counter] = (char) cipher;
//		counter++;
	}
	return cipher;
}

char* decrypt(char *ciphertext, int key) {
	int i = 0;
	char *cipher;
	//	int len = z - a;
	cipher = (char*) malloc(strlen(ciphertext) - 1 * sizeof(char));

//	for (i = 0; i < strlen(ciphertext); i++) {
//	while (ciphertext != '\0') {
	while (i != strlen(ciphertext)) {
		if (isalpha(ciphertext[i]) && isupper(ciphertext[i])
				&& ciphertext[i] != '\0') {
			cipher[i] = ciphertext[i] - key;
		} else if (isalpha(ciphertext[i]) && islower(ciphertext[i])
				&& ciphertext[i] != '\0') {
			if ((ciphertext[i]) > (z - key)) {
				cipher[i] = ciphertext[i] - (26 - key);
			} else
				cipher[i] = ((int) ciphertext[i]) - key;
		} else if (!isalpha(ciphertext[i])) {
			cipher[i] = ciphertext[i];
		} else {
			break;
		}
		i++;
	}
	return cipher;
}

