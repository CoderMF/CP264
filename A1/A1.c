/**
 * -------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student email: faro8180@mylaurier.ca
 * -------------------------
 */
#include <stdio.h>
# include <math.h>
# include <limits.h>
/**
 * CP264: Assignment 1 - Task 1
 * @param base_height
 * @param base_length
 * @param roof_height
 * @param door_height
 * @param door_length
 */
void calculate_cost(float base_height, float base_length, float roof_height,
		float door_height, float door_length) {
	const float roofCost = 11.91;
	const float doorCost = 8.73;
	const float concreteCost = 84.79;
	float totalRoof;
	float totalDoor;
	float totalConcrete;
	float totalRoofCost;
	float totalDoorCost;
	float totalConcreteCost;
	float totalCost;

	printf("House Drawing dimensions (meters):\n");
	printf("BH = %-7.3f  BL = %.3f  \n", base_height, base_length);
	printf("RH = %.3f   \n", roof_height);
	printf("DH = %.3f    DL = %.3f   \n\n", door_height, door_length);

	totalRoof = roof_height * base_length * (1.0 / 2.0);
	totalDoor = door_height * door_length;
	totalConcrete = (base_height * base_length) - totalDoor;

	totalRoofCost = totalRoof * roofCost;
	totalDoorCost = totalDoor * doorCost;
	totalConcreteCost = totalConcrete * concreteCost;
	totalCost = totalRoofCost + totalDoorCost + totalConcreteCost;

	printf("House dimensions (square meter):\n");
	printf("Door area =  %7.3f\n", totalDoor);
	printf("Base area =  %7.3f\n", totalConcrete);
	printf("Roof area =  %7.3f\n\n", totalRoof);

	printf("House cost (CAD):\n");
	printf("Door cost = $%8.3f\n", totalDoorCost);
	printf("Base cost = $%8.3f\n", totalConcreteCost);
	printf("Roof cost = $%8.3f\n", totalRoofCost);
	printf("--------------------\n");
	printf("Total cost = $%.3f\n", totalCost);
	return;
}

/**
 * CP264: Assignment 1 - Task 2
 *  [-:0):           Invalid
 *	[0:20):           No Promotion
 *	[20-35]:          Level 1 Promotion
 *	(35-50]:          Level 2 Promotion
 *	(50-100]:         No Promotion
 *	(100-200]+VIP:    Gold Promotion
 *	(100-200]-VIP:    Silver Promotion
 *	(200, -]:         Special Promotion
 * @param ticket
 * @param vip
 */
void find_promotion(short ticket, char vip) {
	if (vip == 'N' || vip == 'Y') {
		if ((0 <= ticket && ticket < 20) || (50 < ticket && ticket <= 100)) {
			if (vip == 'N') {
				printf("Ticket# %hd: No Promotion - Code# 0", ticket);
			} else {
				printf("Ticket# VIP-%hd: No Promotion - Code# 0", ticket);
			}
		} else if (20 <= ticket && ticket <= 35) {
			if (vip == 'N') {
				printf("Ticket# %hd: Level 1 Promotion - Code# 130", ticket);
			} else {
				printf("Ticket# VIP-%hd: Level 1 Promotion - Code# 130",
						ticket);
			}
		} else if (35 <= ticket && ticket <= 50) {
			if (vip == 'N') {
				printf("Ticket# %hd: Level 2 Promotion - Code# 240", ticket);
			} else {
				printf("Ticket# VIP-%hd: Level 2 Promotion - Code# 240",
						ticket);
			}
		} else if (100 < ticket && ticket <= 200) {
			if (vip == 'N') {
				printf("Ticket# %hd: Silver Promotion - Code# 700", ticket);
			} else {
				printf("Ticket# VIP-%hd: Gold Promotion - Code# 1110", ticket);
			}
		} else if (ticket > 200) {
			if (vip == 'N') {
				printf("Ticket# %hd: Special Promotion - Code# 3333", ticket);
			} else {
				printf("Ticket# VIP-%hd: Special Promotion - Code# 3333",
						ticket);
			}
		} else if (ticket < 0) {
			printf(
					"Ticket# VIP-%hd: Error(find_promotion): Invalid input - Code# -99",
					ticket);
		}
	} else {
		printf("Ticket# %hd: Error(find_promotion): Invalid input - Code# -99",
				ticket);
	}

	return;
}

/**
 * Assignment 1 - Task 3
 * @param num1 (short int)
 * @param num2 (short int)
 * @param opr + , - , * , / , % , ^ (char)
 * @return result (int)
 */
int mini_calculator(short num1, short num2, char opr) {
	short total;
	if (opr == '+') {
		goto Add;
	}

	if (opr == '-') {
		goto Subtract;
	}

	if (opr == '*') {
		goto Times;
	}

	if (opr == '/') {

		if (num2 != 0) {
			goto Divide;
		}
		goto Error;
	}

	if (opr == '%') {
		if (num1 < 0 || num2 < 0) {
			goto Divide;
		}
		if (num2 != 0 && num1 > 0 && num2 > 0) {
			goto Mod;
		}
		goto Error;
	}

	if (opr == '^') {
		if (num2 >= 0) {
			goto Power;
		}
		goto Error;
	}
	goto Error;

	Add: total = num1 + num2;
	goto Finish;
	Subtract: total = num1 - num2;
	goto Finish;
	Times: total = num1 * num2;
	goto Finish;
	Divide: total = num1 / num2;
	goto Finish;
	Power: total = pow(num1, num2);
	goto Finish;
	Mod: total = num1 % num2;
	goto Finish;

	Error: total = -99;
	goto Finish;

	Finish: return total;
}

/**
 * Assignment 1 - Task 4
 * @param num1
 * @param num2
 * @param opr
 */
void mini_calculator2(short num1, short num2, char opr) {
	int total;
	float totaler;
	int max = 2147483647;
	if (opr == '+') {
		goto Add;
	}

	if (opr == '-') {
		goto Subtract;
	}

	if (opr == '*') {
		goto Times;
	}

	if (opr == '/') {

		if (num2 != 0) {
			goto Divide;
		}
		goto Error;
	}

	if (opr == '%') {
		if (num1 < 0 || num2 < 0) {
			goto Divide;
		}
		if (num2 != 0 && num1 > 0 && num2 > 0) {
			goto Mod;
		}
		goto Error;
	}

	if (opr == '^') {
		if (num2 >= 0) {
			goto Power1;
		}
		goto Power2;
	}
	goto Error;

	Add: total = num1 + num2;
	if (total >= INT_MAX || total <= INT_MIN) {
		goto Overflow;
	}
	goto Sentence;

	Subtract: total = num1 - num2;
	if (total >= INT_MAX || total <= INT_MIN) {
		goto Overflow;
	}
	goto Sentence;

	Times: total = num1 * num2;
	if (total >= INT_MAX || total <= INT_MIN || sizeof(total) > max) {
		goto Overflow;
	}
	goto Sentence;

	Divide: total = num1 / num2;
	if (total >= INT_MAX || total <= INT_MIN || sizeof(total) > max) {
		goto Overflow;
	}
	goto Sentence;

	Power1: total = pow(num1, num2);
	if (total >= INT_MAX || total <= INT_MIN || sizeof(total) > max) {
		goto Overflow;
	}
	goto Sentence;

	Power2: totaler = pow(num1, num2);
	goto Sentence2;

	Mod: total = num1 % num2;
	if (total >= INT_MAX || total <= INT_MIN || sizeof(total) > max) {
		goto Overflow;
	}
	goto Sentence;

	Overflow: printf("%hd %c %hd = OVERFLOW\n", num1, opr, num2);
	goto Finish;

	Error: printf("%hd %c %hd = ERROR\n", num1, opr, num2);
	goto Finish;

	Sentence: printf("%hd %c %hd = %d\n", num1, opr, num2, total);
	goto Finish;

	Sentence2: printf("%hd %c %hd = %.4f\n", num1, opr, num2, totaler);

	Finish: return;
}
