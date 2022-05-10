/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 
 * Student Email: 
 * ---------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
#include "A5.h"

//---------------------- Task 1 ---------------------------------
void analyze_file(const char *filename, const char *filename2) {
	FILE *out_file = NULL;
	out_file = fopen(filename2, "a");
	if (out_file == NULL) {
		printf("Error(analyze_file): Could not open file %s\n", filename);
		return;
	}
	FILE *in_file = NULL;
	in_file = fopen(filename, "r");

	if (in_file == NULL) {
		fprintf(out_file, "Error(analyze_file): Could not open file %s\n",
				filename);
		fclose(out_file);
		return;
	}

	int para = 1, lines = 1, words = 0, alpha = 0, num = 0, other = 0, letters =
			0;
	char ch, line[MAX];

// goes character by character
	while ((ch = fgetc(in_file)) != EOF) {
		if ((isalpha(ch) || isdigit(ch)) || !(isspace(ch)))
			letters++;
		if (ch == '\n')
			lines++;
		if (isalpha(ch))
			alpha++;
		if (isdigit(ch))
			num++;
		if (!(isalpha(ch) || isdigit(ch) || isspace(ch)))
			other++;
		if (ch == ' ')	// fix issue here
			words++;

	}

	// reset pointer
	fseek(in_file, 0, SEEK_SET);
	// goes line by line
	while (fgets(line, sizeof(line), in_file)) {
		if (line[0] == '\n')
			para++;
		else {
			words++;
		}
//		if (line == '\n' && !(line[0] == '\n'))
//			words++;
//		if (i == MAX) {
//			i = 0;
//		}
//		i++;

	}

	fprintf(out_file, "Analyzing file %s:\n", filename);
	fprintf(out_file, "#Paragraphs = %d\n", para);
	fprintf(out_file, "#lines = %d\n", lines);
	fprintf(out_file, "#Words = %d\n", words);
	fprintf(out_file, "#Characters = %d\n", letters);
	fprintf(out_file, "Alpha = %d\n", alpha);
	fprintf(out_file, "Numerical = %d\n", num);
	fprintf(out_file, "Other = %d\n", other);
	fprintf(out_file, "\n");

	fclose(in_file);
	fclose(out_file);

	return;
}

//---------------------- Task 2 ---------------------------------
void format_file1(const char *in_file, const char *out_file) {
	FILE *outFile = NULL;
	outFile = fopen(out_file, "w");
	FILE *inFile = NULL;
	inFile = fopen(in_file, "r");
	if (inFile == NULL) {
		fprintf(outFile, "Error(format_file1): Could not open file %s\n",
				in_file);
		fclose(outFile);
		return;
	}
	char line[MAX];
	int counter = 0, i;
	while (fgets(line, sizeof(line), inFile)) {
		for (i = 0; i < strlen(line) - 1; i++) {
			if (line[i] != '\n') {
				fprintf(outFile, "%c", line[i]);
			}
			if (line[i] == ' ') {
				counter++;
			}
			if ((line[i] == ',') && line[i + 1] != ' ') {
				fprintf(outFile, " ");
				counter++;
			}
			if (line[i] == ')' && line[i + 1] != ' ' && line[i + 1] != '.') {
				fprintf(outFile, " ");
				counter++;
			}
			if (line[i] == '.') {
				fprintf(outFile, " ");
				counter++;
			}
			if (isalpha(line[i]) && line[i + 1] == '\n') {
				fprintf(outFile, " ");
				counter++;
			}

			if (counter == 4) {
				fprintf(outFile, "\n");
				counter = 0;
			}
		}
	}
	fprintf(outFile, ".\n");
	fclose(inFile);
	fclose(outFile);
	return;
}

//---------------------- Task 3 ---------------------------------
void format_file2(const char *in_file, const char *out_file) {
	FILE *outFile = NULL;
	outFile = fopen(out_file, "w");
	FILE *inFile = NULL;
	inFile = fopen(in_file, "r");

	if (inFile == NULL) {
		fprintf(outFile, "Error(format_file2): Could not open file %s\n",
				in_file);
		fclose(outFile);
		return;
	}

	int i = 0;
	char line[MAX];
	int len;
//	char ch;

	// goes line by line
	while (fgets(line, sizeof(line), inFile)) {
		len = strlen(line);

//		for (i = 0; i < MAX; i++) {
//			if ((isalpha(line[i]) || isdigit(line[i]) || isspace(line[i]))) {
//				if (line[i] == '\n' && line[0] != '\n') {
//					printf("Test line pos %c", line[i]);
//					fprintf(outFile, ".");
//				}
//
//			}
//		}

		if (line[0] != '\n') {
			line[0] = toupper(line[0]);
			for (i = 0; i < len; i++) {
//				if (line[len] != '.' && line[len - 1] == '.') {	// fix here
//					line[len - 1] = '.';
////					fprintf(outFile, "%c", line[len - 1]);
//				}
				if ((isalpha(line[i]) || isdigit(line[i]) || isspace(line[i]))) {
					if ((line[i] == '\n' || line[i] == line[len])
							&& line[0] != '\n') {
						line[i] = '.';
					}
					fprintf(outFile, "%c", line[i]);
				}
			}

		}

		fprintf(outFile, "\n");
	}

	fclose(inFile);
	fclose(outFile);
	return;
}

//---------------------- Task 4 ---------------------------------
void get_city_details(const char *in_file, const char *out_file, char *city) {
	FILE *outFile = NULL;
	outFile = fopen(out_file, "a");
	FILE *inFile = NULL;
	inFile = fopen(in_file, "r");
	fprintf(outFile, "Searching for %s in \"%s\":\n", city, in_file);
	if (inFile == NULL) {
		fprintf(outFile, "Error(get_city_details): Could not open file %s\n",
				in_file);
		fclose(outFile);
		return;
	}

	char line[MAX];
	char buffer1[20], buffer2[20], buffer3[20], buffer4[20], buffer5[20],
			buffer6[20], buffer7[20];
	char name[20], pop[11], area[11];
	int found = 0;
	char *filename, prov[20];

	while (fgets(line, sizeof(line), inFile)) {
		sscanf(line, "%s %s %s %s %s %s %s %s %s %s", buffer1, buffer2, name,
				buffer3, pop, buffer4, buffer5, buffer6, buffer7, area);
//		printf("Name %s Pop %s Area %s\n", name, pop, area);
		if (strcmp(name, city) == 0) {

			strcpy(prov, in_file);
			filename = strtok(prov, ".");
			filename[0] = toupper(filename[0]);
			fprintf(outFile, "Province = %s\n", filename);
			fprintf(outFile, "Population = %s\n", pop);
			fprintf(outFile, "Area = %s\n", area);
			found = 1;
		}

	}

	if (found == 0) {
		fprintf(outFile, "Could not find %s in \"%s\"\n", city, in_file);
	}
	fprintf(outFile, "\n");
	fclose(inFile);
	fclose(outFile);
	return;
}

//---------------------- Task 5 ---------------------------------
void replace_is(const char *filename, char *new_str) {
	FILE *inFile = NULL;
	inFile = fopen(filename, "r+");

	FILE *temp = NULL;
	temp = fopen("temp.txt", "w");

	if (inFile == NULL) {
		fprintf(inFile, "Error(get_city_details): Could not open file %s\n",
				filename);
		printf("Error(get_city_details): Could not open file %s\n", filename);
		return;
	}

	char line[MAX];
	char buffer1[20], buffer2[20], buffer3[20], buffer4[20], buffer5[20],
			buffer6[20], buffer7[20], buffer8[20];
	char name[20], pop[11], area[11];
	int counter = 0;

	while (fgets(line, sizeof(line), inFile)) {
		counter = 0;
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] == ' ' && !(isalpha(line[i]) || isdigit(line[i]))) {

				counter++;
			}

		}

		if (counter == 10) {
			sscanf(line, "%s %s %s %s %s %s %s %s %s %s %s", buffer1, buffer2,
					buffer8, name, buffer3, pop, buffer4, buffer5, buffer6,
					buffer7, area);
			if (strcmp(buffer3, "is") == 0 || strcmp(buffer7, "is") == 0) {
				if (strcmp(buffer3, "is") == 0)
					strcpy(buffer3, new_str);
				if (strcmp(buffer7, "is") == 0)
					strcpy(buffer7, new_str);
			}
			fprintf(temp, "%s %s %s %s %s %s %s %s %s %s %s\n", buffer1,
					buffer2, buffer8, name, buffer3, pop, buffer4, buffer5,
					buffer6, buffer7, area);
		} else {

			sscanf(line, "%s %s %s %s %s %s %s %s %s %s", buffer1, buffer2,
					name, buffer3, pop, buffer4, buffer5, buffer6, buffer7,
					area);
			//		printf("Name %s Pop %s Area %s\n", name, pop, area);
			if (strcmp(buffer3, "is") == 0 || strcmp(buffer7, "is") == 0) {
				if (strcmp(buffer3, "is") == 0)
					strcpy(buffer3, new_str);
				if (strcmp(buffer7, "is") == 0)
					strcpy(buffer7, new_str);
			}
			fprintf(temp, "%s %s %s %s %s %s %s %s %s %s\n", buffer1, buffer2,
					name, buffer3, pop, buffer4, buffer5, buffer6, buffer7,
					area);
		}

	}

	fclose(temp);
	temp = fopen("temp.txt", "r");
//	fseek(inFile, 0, SEEK_SET);
//	fseek(temp, 0, SEEK_SET);
	rewind(inFile);

	// create new loop and put stuff from temp into inFile then delete temp
	while (fgets(line, sizeof(line), temp)) {
		fprintf(inFile, "%s", line);
	}
	fclose(temp);
	remove("temp.txt");
	fclose(inFile);
	return;
}

