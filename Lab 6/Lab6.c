/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 
 * Student Email: 
 * ---------------------------------
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_letters(const char *filename, int counters[26]);
void write_results(const char *filename, int counters[26]);
void append_sum(const char *filename, int counters[26]);

int main() {
	setbuf(stdout, NULL);

	char filename[20] = "text1.txt";
	int counters[26] = { 0 };

	count_letters(filename, counters);

	filename[4] = '2';
	write_results(filename, counters);

	append_sum(filename, counters);

	printf("Check text2.txt for output\n");

	return 0;
}

void count_letters(const char *filename, int counters[26]) {
	FILE *file = NULL;
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error(count_letters): Could not open file %s\n", filename);
		return;
	}
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
			'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
			'y', 'z' };
	char ch;
	int i;

	while ((ch = fgetc(file)) != EOF) {
		if (isalpha(ch)) {
			for (i = 0; i < 26; i++) {
				if (alphabet[i] == tolower(ch)) {
					counters[i]++;
				}
			}
		}
	}
	fclose(file);

	return;
}

void write_results(const char *filename, int counters[26]) {
	FILE *file = NULL;
	file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error(write_results): Could not open file %s\n", filename);
		return;
	}
	int i;
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
			'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
			'y', 'z' };
	for (i = 0; i < 26; i++) {
		fprintf(file, "count(%c) = %d\n", alphabet[i], counters[i]);
	}
	fclose(file);
	return;

}

void append_sum(const char *filename, int counters[26]) {
	FILE *file = NULL;
	file = fopen(filename, "a");
	if (file == NULL) {
		printf("Error(append_sum): Could not open file %s\n", filename);
		return;
	}
	int i, sum = 0;
	for (i = 0; i < 26; i++) {
		sum += counters[i];
	}
	fprintf(file, "Total = %d", sum);
	fclose(file);
	return;
}

