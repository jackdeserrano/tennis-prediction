#include <stdio.h>
#include <stdlib.h>

double p_wins_game(double p_0) {
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

// final set tiebreak needs 10 points
double p_wins_tiebreak(double p_s, double p_r, int serving_first) {
	double p_0 = serving_first ? p_s : p_r;
	double p_1 = serving_first ? p_r : p_s;
	double q_0 = 1 - p_0;
	double q_1 = 1 - p_1;
	
	double p = 0;

	// reaching 6-6
	p +=       q_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * p_1;
	p += 36  * p_0 * q_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * p_1 * q_1;
	p += 225 * p_0 * p_0 * q_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * p_1 * q_1 * q_1;
	p += 400 * p_0 * p_0 * p_0 * q_0 * q_0 * q_0 * p_1 * p_1 * p_1 * q_1 * q_1 * q_1;
	p += 225 * p_0 * p_0 * p_0 * p_0 * q_0 * q_0 * p_1 * p_1 * q_1 * q_1 * q_1 * q_1;
	p += 36  * p_0 * p_0 * p_0 * p_0 * p_0 * q_0 * p_1 * q_1 * q_1 * q_1 * q_1 * q_1;
	p +=       p_0 * p_0 * p_0 * p_0 * p_0 * p_0 * q_1 * q_1 * q_1 * q_1 * q_1 * q_1;

	// 8-6, 9-7, . . .
	p *= p_0 * p_1 / (p_0 * p_1 + q_0 * q_1);

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

	return p;
}

double p_wins_set(double p_s, double p_r, int serving_first, int has_tiebreak) {
	double p_0 = serving_first ? p_wins_game(p_s) : p_wins_game(p_r);
	double p_1 = serving_first ? p_wins_game(p_r) : p_wins_game(p_s);
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
	p *= has_tiebreak ? p_wins_tiebreak(p_s, p_r, serving_first, 0) : p_0 * p_1 / (p_0 * p_1 + q_0 * q_1);

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

int main(void) {
	printf("%lf\n", p_wins_set(0.8,0.3,1,1));
	return 0;
}

