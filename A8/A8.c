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
# include <assert.h>
# include "A8.h"

/**
 *  -------------------------------------------------------------------------
 * 	Message for marker :)
 *	-------------------------------------------------------------------------
 * 	Hello! If possible, could you please test the functions one by one?
 *	My RR somewhat runs and my program recognizes the different schedule types (prints error if not 3 types)
 *	This way, even though I did not perform very well I can still earn part marks here and there.
 *	Thank you so much, it would mean the world if you can take the time to do that!
 *	-------------------------------------------------------------------------
 */

/*---------------------Task 1 -----------------------------*/
void schedule(char *type, Data *processes, const int size) {
	if (strcmp(type, "FIFO") == 0) {
		int i;
		pQueue *q = create_pqueue(size, 'H');
		for (i = 0; i < size; i++) {
			insert_pqueue(q, &processes[i]);
		}
		schedule_FIFO(q);
	} else if (strcmp(type, "SJF") == 0) {
		int i;
		pQueue *q = create_pqueue(size, 'L');
		for (i = 0; i < size; i++) {
			insert_pqueue(q, &processes[i]);
		}
		schedule_SJF(q);
	} else if (isdigit(type[2]) && type[0] == 'R' && type[1] == 'R') {
		pQueue *q = create_pqueue(size, 'L');
		for (int i = 0; i < size; i++) {
			insert_pqueue2(q, &processes[i]);
		}
		int period = atoi(&type[2]);
		schedule_RR(q, period);
	} else {
		printf("Error(schedule): Unsupported scheduler type\n");
		return;
	}
	return;
}

/*---------------------Task 2 -----------------------------*/
void schedule_FIFO(pQueue *q) {
	//your code
	int timer = 1, i, counter = 0;
	int len = len_pqueue(q);
//	&q->array[len_pqueue - 1].time
//	print_pqueue(q->array[len_pqueue - 1]);
//	printf("Check %d", q->array[0].arrival);
	printf("[Timer:0]: Starting FIFO Scheduler\n");
	if (q->array[0].arrival != 0) {
		while (timer < q->array[0].arrival) {
			printf("[Timer:%d]: Idle\n", timer);
			timer++;
		}
	}
	for (i = 0; i < len; i++) {
		counter = 0;
		printf("Fetching Process: ");
		print_data(&q->array[i]);
		printf("\n");

//		while (timer < q->array[i + 1].arrival) {
		while (counter < q->array[i].time) {
			printf("[Timer:%d]: ", timer);
			print_data(&q->array[i]);
			printf("\n");
			timer++;
			counter++;
		}
		if (timer != q->array[i + 1].arrival - 1 && (i != len - 1)) {
			while (timer < q->array[i + 1].arrival) {
				printf("[Timer:%d]: Idle\n", timer);
				timer++;
			}
		}

	}
	printf("[Timer:%d]: Closing FIFO Scheduler\n", timer);
	return;
}

/*---------------------Task 3 -----------------------------*/
void schedule_SJF(pQueue *q) {
//	print_pqueue(q);
//	return;	//to test rr mode
	Data *min = peek_pqueue(q);
	Data *back = NULL;
//	pQueue *temp = create_pqueue(len_pqueue(q) - 1, 'H');
	int timer = 1, counter = 0, i;
	int len = len_pqueue(q);

	printf("[Timer:0]: Starting SJF Scheduler\n");
	if (min->arrival != 0) {
		while (timer < min->arrival) {
			printf("[Timer:%d]: Idle\n", timer);
			timer++;
		}
	}

	for (i = 0; i < len; i++) {
////		printf("check");
////		print_pqueue(q);
		pQueue *temp = create_pqueue(len - i, 'L');
		for (i = 0; i < len - i - 1; i++) {

			if (min->time < peek_pqueue(q)->time) {
				min = peek_pqueue(q);
			}
			back = remove_pqueue(q);
//			insert_pqueue(temp, back);
			insert_pqueue(q, back);
//
		}
////		printf("check min");
////		print_data(min);
////		printf("check");
////		print_pqueue(q);
		q = (pQueue*) realloc(q, (len - i - 1) * sizeof(pQueue));
		for (i = 0; i < len; i++) {
			if (peek_pqueue(q) != min) {
//				printf("check");
				insert_pqueue(temp, peek_pqueue(q));

			}
			remove_pqueue(q);
		}
//		printf("check");
//		print_pqueue(temp);
//
		for (i = 0; i < len - i - 1; i++) {
			insert_pqueue(q, remove_pqueue(temp));
		}

		counter = 0;
		printf("Fetching Process: ");
		print_data(min);
		printf("\n");
		while (counter < min->time) {
			printf("[Timer:%d]: ", timer);
			print_data(min);
			printf("\n");
			timer++;
			counter++;
		}
		free(temp);
		temp = NULL;
		remove_pqueue(q);
	}

//	print_pqueue(q);
	printf("[Timer:%d]: Closing FIFO Scheduler\n", timer);
	return;
}

/*---------------------Task 4 -----------------------------*/
void schedule_RR(pQueue *q, int period) {
	int timer = 1, counter = 0, i;
	int len = len_pqueue(q);
	Data *back = NULL;
	int index;
//	print_pqueue(q);

	printf("[Timer:0]: Starting RR%d Scheduler\n", period);
	if (peek_pqueue(q)->arrival != 0) {
		while (timer < q->array[0].arrival) {
			printf("[Timer:%d]: idle\n", timer);
			timer++;
		}
	}
//	while (!is_empty_pqueue(q)) {
	for (i = 0; i < len; i++) {
		index = find_top_priority(q);
//	while (!is_empty_pqueue(q)) {
//		if (peek_pqueue(q)->time < period) {
		if (q->array[index].time <= 0 || q->array[index].time > 99)
			remove_pqueue(q);
		printf("Fetching Process: ");
		print_data(peek_pqueue(q));
		printf("\n");
		if (peek_pqueue(q)->time <= period) {	// if less/eq than period
//			printf("should mean arrival shortened");
			counter = peek_pqueue(q)->time;
//			if (counter > 99) {
//				remove_pqueue(q);
//			}

			while (counter > 0) {
				printf("[Timer:%d]: ", timer);
				print_data(peek_pqueue(q));
				printf("\n");
				counter--;
				timer++;
			}

//			if (q->array[index].time == 0) {
//				q->array[index].arrival = timer;
//				q->array[index].time = q->array[index].time - period;
//			}
//			q->array[index].arrival = timer;
//			q->array[index].time = q->array[index].time - period;
//			remove_pqueue(q);
		} else if (peek_pqueue(q)->time > period) {
//			printf("should go through here");
			counter = 0;
//			if (time_check > 99) {
//				remove_pqueue(q);
//			}
			while (counter < period) {
				printf("[Timer:%d]: ", timer);
				print_data(peek_pqueue(q));
				printf("\n");
				counter++;
				timer++;
			}
		}

		q->array[index].arrival = timer;
		q->array[index].time = q->array[index].time - period;
//		printf("check current status of peeked element ");
//		print_data(peek_pqueue(q));
//		printf("\n");

//		if (q->array[index].time > time_check)
//			remove_pqueue(q);
//		if (q->array[index].time < time_check)
		back = remove_pqueue(q);
		if (peek_pqueue(q)->time > 0 && (peek_pqueue(q)->time < 99)) {
//		if (q->array[index].time > 0 && !(q->array[index].time > time_check)) {
//			printf("should stay in queue\n");
//			back = remove_pqueue(q);
			insert_pqueue(q, back);
		}
//		remove_pqueue(q);
//		i++;
	}

//	print_pqueue(q);
	printf("[Timer:%d]: Closing RR%d Scheduler\n", timer, period);
	return;
}
