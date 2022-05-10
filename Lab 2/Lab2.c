#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * --------------------------------------------------------
 * Computes the value of a using the four integer input parameters: r,y,x and b.
 * The value of a is computed according to the following equation:
 *		a = floor((cube(3)-y)/x) - square_root(b to power 4))
 * The function prints the output in a format similar to the following
 *		[r = 2, y = 3, x = 2, b = 2] --> a = -2.0
 * The function also returns the value of a, which is of type double
 * ----------------------------------------------------------
 */
void solve2(short w, int x, float y, double z) {
	double r;
	double p1, p2, p3;

	p1 = ((log(y) * fabs(w - x)) / sqrt(z));
	p2 = (exp(4) * ceil((y * pow(z, 3)) / x));
	p3 = (cbrt((pow(x, y) - y)));

	r = p1 + p2 - p3;

	printf("w =       %hd         x =       %d\n", w, x);
	printf("y =       %-5.2f     z =       %-8.4lf\n", y, z);
	printf("r =       %.4lf\n", r);
	return;
}

/**
 * --------------------------------------------------------
 * Generates and returns a random integer.
 * the mode input parameter controls how the random number is generated, as follows:
 * 1-	If mode is �1�: The function generates a random number in the range [0,x1], i.e. inclusive both ends.
 * 2-	If mode is �2�: The function generates a random number in the range (0,x2), i.e. exclusive both ends.
 * 3-	If mode is �i�: The function generates a random number in the range [x1,x2], i.e. inclusive both ends.
 * 4-	If mode is �x�: The function generates a random number in the range (x1,x2), i.e. exclusive both ends.
 * 5-	If mode is �L�: The function generates a random number in the range [x1,x2), i.e. inclusive only from the left which is x1.
 * 6-	If mode is �R�: The function generates a random number in the range (x1,x2], i.e. inclusive only from the right which is x2.
 * 7-	For any other mode value, the function generates a random number between 0 and RAND_MAX.
 * The function is implemented using switch-case statement.
 * Assume that x1 is always less than x2 by at least 2.
 * ----------------------------------------------------------
 */
unsigned int rand_int(unsigned int x1, unsigned int x2, char mode) {
	int random;
	switch (mode) {
	case '1':
		random = rand() % (x1 + 1);
		break;
	case '2':
		random = (rand() % (x2)) + 1;
		break;
	case 'i':
		random = (rand() % (x2 - x1 + 1)) + x1;
		break;
	case 'x':
		random = (rand() % (x2 - x1 - 1)) + x1 + 1;
		break;
	case 'L':
		random = (rand() % (x2 - x1)) + x1;
		break;
	case 'R':
		random = (rand() % (x2 - x1)) + x1 + 1;
		break;

	default:
		random = (rand() % RAND_MAX) + 1;
	}
	return random;
}

