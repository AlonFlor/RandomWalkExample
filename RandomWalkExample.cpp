// RandomWalkExample.cpp : Defines the entry point for the application.
//

#include "RandomWalkExample.h"
#include "RandomWalker.h"
#include <random>
#include <vector>
#include <string>

using namespace std;
FILE* fp;
FILE* fp_dist;
FILE* fp_avg;
vector<float> average_walk;
vector<vector<int>> distribution;
random_device r;
default_random_engine e1(r());
uniform_real_distribution<float> probability_run(0, 1);

int num_attempts = 10000;
int length_of_walk = 100;

void runLoop(bool isCorrelated, int initial_direction, float prob) {
	for (int i = 0; i < num_attempts; ++i) {
		Walker w = Walker(prob, isCorrelated);
		fprintf(fp, "%d,%d", i + 1, w.position);
		distribution[0][w.position + length_of_walk] += 1;
		average_walk[0] += w.position;

		//first move
		if (initial_direction == -1) {
			w.position -= 1;
			w.last_direction_right = false;
		}
		else if (initial_direction == 0) {
			w.Simple_Move(probability_run(e1));
		}
		else {
			w.position += 1;
			w.last_direction_right = true;
		}
		fprintf(fp, ",%d", w.position);
		average_walk[1] += w.position;
		distribution[1][w.position + length_of_walk] += 1;

		//inner loop
		for (int j = 1; j < length_of_walk; ++j) {
			w.Move(probability_run(e1));
			fprintf(fp, ",%d", w.position);
			average_walk[j + 1] += w.position;
			distribution[j+1][w.position + length_of_walk] += 1;
		}
		fprintf(fp, "\n");
	}
}

//print the averages for the current case and reset average_walk
void process_avg(char str[]) {
	fprintf(fp_avg, "%s", str);
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp_avg, ",%f", average_walk[i] / num_attempts);
		average_walk[i] = 0.0f;
	}
	fprintf(fp_avg, "\n");
}

//print the distribution for the current case and reset distribution
void process_dist() {
	for (int i = 0; i < 2 * length_of_walk; ++i) {
		fprintf(fp_dist, "%d", i - length_of_walk);
		for (int j = 0; j < length_of_walk + 1; ++j) {
			fprintf(fp_dist, ",%d", distribution[j][i]);
		}
		fprintf(fp_dist, "\n");
	}

	//reset
	for (int i = 0; i < length_of_walk + 1; ++i) {
		for (int j = 0; j < 2 * length_of_walk; ++j) {
			distribution[i][j] = 0;
		}
	}
}

void run_case(string case_name, bool isCorrelated, int initial_direction, float prob) {
	char* case_name_str = &case_name[0];
	string rawfile_case_name = case_name + ".csv";
	const char* rawfile_case_name_str = rawfile_case_name.c_str();
	string distfile_case_name = "Dist_" + rawfile_case_name;
	const char* distfile_case_name_str = distfile_case_name.c_str();

	printf("%s\n", case_name_str);
	fp = fopen(rawfile_case_name_str, "w");
	fp_dist = fopen(distfile_case_name_str, "w");
	fprintf(fp, "attempt number");
	fprintf(fp_dist, "position");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
		fprintf(fp_dist, ",step %d", i);
	}
	fprintf(fp, "\n");
	fprintf(fp_dist, "\n");
	runLoop(isCorrelated, initial_direction, prob);
	process_avg(case_name_str);
	process_dist();
	fclose(fp);
	fclose(fp_dist);
}

int main()
{
	//initialize average location
	fp_avg = fopen("averages.csv", "w");
	fprintf(fp_avg, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp_avg, ",step %d", i);
		average_walk.push_back(0.0f);
	}
	fprintf(fp_avg, "\n");

	//initialize distribution
	for (int i = 0; i < length_of_walk + 1; ++i) {
		vector<int> time_step_distribution;
		for (int j = 0; j < 2*length_of_walk; ++j) {
			time_step_distribution.push_back(0);
		}
		distribution.push_back(time_step_distribution);
	}

	string str;
	

	str = "Simple_Random_Walk_ProbRight=0.3";
	run_case(str, false, 0, 0.3);

	str = "Simple_Initial_Right_Random_Walk_ProbRight=0.3";
	run_case(str, false, 1, 0.3);

	str = "Correlated_Random_Walk_ProbTurn=0.3";
	run_case(str, true, 0, 0.3);

	str = "Correlated_Initial_Right_Random_Walk_ProbTurn=0.3";
	run_case(str, true, 1, 0.3);



	str = "Simple_Random_Walk_ProbRight=0.5";
	run_case(str, false, 0, 0.5);

	str = "Simple_Initial_Right_Random_Walk_ProbRight=0.5";
	run_case(str, false, 1, 0.5);

	str = "Correlated_Random_Walk_ProbTurn=0.5";
	run_case(str, true, 0, 0.5);

	str = "Correlated_Initial_Right_Random_Walk_ProbTurn=0.5";
	run_case(str, true, 1, 0.5);



	str = "Simple_Random_Walk_ProbRight=0.7";
	run_case(str, false, 0, 0.7);

	str = "Simple_Initial_Right_Random_Walk_ProbRight=0.7";
	run_case(str, false, 1, 0.7);

	str = "Correlated_Random_Walk_ProbTurn=0.7";
	run_case(str, true, 0, 0.7);

	str = "Correlated_Initial_Right_Random_Walk_ProbTurn=0.7";
	run_case(str, true, 1, 0.7);



	fclose(fp_avg);

	printf("Done");
	return 0;
}