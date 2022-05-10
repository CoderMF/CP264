/**
 -------------------------
 Student Name: Maham Farooq
 Student ID: 
 Student email: 
 -------------------------
 **/
# include <stdio.h>

void t1();
void t2();
void t3();

void main() {
	setbuf(stdout, NULL);
	t1();
	printf("\n\n");
	t2();
	printf("\n\n");
	t3();
	return;
}

void t1() {
	int tall;
	int shorter;
	float total;
	double avg_height;
	char symbol = 84;
	const int val = 43;

	printf("Enter number of tall trees: ");
	scanf("%d", &tall);
	printf("Enter number of short trees: ");
	scanf("%d", &shorter);
	total = tall + shorter;
	avg_height = (val / total);
	//printing report
	printf("Number of %c trees = %d\n", symbol, tall);
	printf("Number of %c trees = %d\n", (symbol - 1), shorter);
	printf("Average height = %.2lf", avg_height);
	return;
}

void t2() {
	unsigned int year;
	short month;
	int day;
	char university[30];
	printf("Enter year: ");
	scanf("%u", &year);

	printf("Enter month: ");
	scanf("%hd", &month);

	printf("Enter day: ");
	scanf("%d", &day);

	printf("Enter University: ");
	scanf("%s", university);

	printf("\n");
	printf("This is %s University\n", university);
	printf("Today is :%d/%hd/%u", day, month, year);

	return;
}

void t3() {
	printf("Hints for C Language:\n");
	printf("Insert \\n\ at end of printf for newline.\n");
	printf("Use \"double quotes\" not 'single quotes' for strings.\n");
	printf("Use %%d for integer, %%f for float and %%lf for double.\n");
	return;
}
