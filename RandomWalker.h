#include "RandomWalkExample.h"

class Walker {
public:
	int position = 0;
	float probability;
	bool is_correlated;
	bool last_direction_right;

	Walker()
	{

	}

	Walker(float probability_in, bool is_correlated_in) {
		probability = probability_in;
		is_correlated = is_correlated_in;
	}

	void Move(float prob_result) {

		if (is_correlated) {
			bool turn = prob_result < probability;
			if (turn) {
				//turning
				if (last_direction_right) {
					position -= 1;
					last_direction_right = false;
				}
				else {
					position += 1;
					last_direction_right = true;
				}
			}
			else {
				//not turning
				if (last_direction_right) {
					position += 1;
					last_direction_right = true;
				}
				else {
					position -= 1;
					last_direction_right = false;
				}
			}
		}
		else {
			Simple_Move(prob_result);
		}
		
	}

	void Simple_Move(float prob_result) {
		//simple random walk
		bool right = prob_result < probability;
		if (right) {
			position += 1;
			last_direction_right = true;
		}
		else {
			position -= 1;
			last_direction_right = false;
		}
	}
};