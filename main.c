#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// p_0 = the probability of winning a point
double p_wins_game(double p_0) {
	assert(p_0 >= 0 && p_0 <= 1);

	double q_0 = 1 - p_0;

	double p = 0;

	// reaching deuce
	p += 20 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0;

	// winning after deuce
	p *= p_0 * p_0 / (p_0 * p_0 + q_0 * q_0);

	// winning before deuce
	p += p_0 * p_0 * p_0 * p_0 * (1 + 4 * q_0 + 10 * q_0 * q_0);

	return p;
}

// p_0 = the probability of winning a service point
// p_1 = the probability of winning a return point
double p_wins_tiebreak(double p_0, double p_1, int is_to_ten) {
	assert(p_0 >= 0 && p_0 <= 1);
	assert(p_1 >= 0 && p_1 <= 1);

	double q_0 = 1 - p_0;
	double q_1 = 1 - p_1;
	
	double p = 0;

	if (is_to_ten) {

		// reaching 9-9
		p +=         q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 81    * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 1296  * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 7056  * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 15876 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 15876 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 7056  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 1296  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 81    * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p +=         p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	} else {
		
		// reaching 6-6
		p +=       q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 36  * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 225 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 400 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 225 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 36  * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p +=       p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	}

	// . . . , 11-9, 12-10, . . .
	p *= p_0 * p_1 / (p_0 * p_1 + q_0 * q_1);

	if (is_to_ten) {

		// 10-0
		p += p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * p_1 * p_1;

		// 10-1
		p += 5 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 5 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;

		// 10-2
		p += 10 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 30 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 15 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;

		// 10-3
		p += 20 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 90 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 90 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 20 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;

		// 10-4
		p += 35  * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 210 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 315 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 140 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 15  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;

		// 10-5
		p += 21  * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 245 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 735 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 735 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 245 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 21  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;

		// 10-6
		p += 7    * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 168  * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 980  * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 1960 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 1470 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 392  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 28   * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

		// 10-7
		p += 8    * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 224  * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 1568 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 3920 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 3920 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 1568 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 224  * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 8    * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

		// 10-8
		p += 9    * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 288  * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 2352 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 7056 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 8820 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 4704 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 1008 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p += 72   * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;
		p +=        p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	} else {
		
		// 7-0
		p += p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * p_1;
		
		// 7-1
		p += 3 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * p_1;
		p += 4 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * p_1 * q_1;
		
		// 7-2
		p += 6  * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1;
		p += 16 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * q_1;
		p += 6  * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1 * q_1;
		
		// 7-3
		p += 10 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 40 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 30 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 4  * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1 * q_1 * q_1;
		
		// 7-4
		p += 5   * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 50  * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 100 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 50  * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 5   * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		
		// 7-5
		p +=       p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
		p += 30  * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
		p += 150 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
		p += 200 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
		p += 75  * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
		p += 6   * p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	}

	return p;
}

double p_wins_set(double p_s, double p_r, int has_tiebreak, int tiebreak_is_to_ten) {
	assert(p_s >= 0 && p_s <= 1);
	assert(p_r >= 0 && p_r <= 1);

	double p_0 = p_wins_game(p_s);
	double p_1 = p_wins_game(p_r);
	double q_0 = 1 - p_0;
	double q_1 = 1 - p_1;

	double p = 0;

	// reaching 6-6 (5-5 and then splitting next two games)
	p +=       q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1;
	p += 25  * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1;
	p += 100 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1;
	p += 100 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1;
	p += 25  * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * q_1 * q_1 * q_1 * q_1;
	p +=       p_0 * p_0 * p_0 * p_0 * p_0 * q_1 * q_1 * q_1 * q_1 * q_1;
	
	p *= q_0 * p_1 + p_0 * q_1;

	// after reaching 6-6
	p *= has_tiebreak ? p_wins_tiebreak(p_s, p_r, tiebreak_is_to_ten) : p_0 * p_1 / (p_0 * p_1 + q_0 * q_1);

	// 6-0
	p += p_0 * p_0 * p_0 * p_1 * p_1 * p_1;

	// 6-1
	p += 3 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1;
	p += 3 * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1;

	// 6-2
	p += 6  * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1;
	p += 12 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * p_1 * q_1;
	p += 3  * p_0 * p_0 * p_0 * p_0 * p_1 * p_1 * q_1 * q_1;

	// 6-3
	p += 4  * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1;
	p += 24 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1;
	p += 24 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1;
	p += 4  * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1;

	// 6-4
	p += 5  * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1;
	p += 40 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1;
	p += 60 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1;
	p += 20 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1;
	p +=      p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1 * q_1;

	// 7-5 (5-5 and then winning next two games)
	p +=       p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;	
	p += 25  * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
	p += 100 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
	p += 100 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
	p += 25  * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
	p +=       p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	return p;
}

double p_wins_match(double p_s, double p_r, int is_grand_slam) {
	assert(p_s >= 0 && p_s <= 1);
	assert(p_r >= 0 && p_r <= 1);

	double p_0 = p_wins_set(p_s, p_r, 1, 0);
	double q_0 = 1 - p_0;

	if (is_grand_slam) {

		double p_1 = p_wins_set(p_s, p_r, 1, 1);
		return p_0 * p_0 * (p_0 + 3 * p_0 * q_0 + 6 * p_1 * q_0 * q_0);
	}

	return p_0 * p_0 * (1 + 2 * q_0);
}
