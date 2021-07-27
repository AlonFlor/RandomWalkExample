// RandomWalkExample.cpp : Defines the entry point for the application.
//

#include "RandomWalkExample.h"
#include "RandomWalker.h"
#include <random>
#include <vector>

using namespace std;
FILE* fp;
FILE* fp_avg;
vector<float> average_walk;
random_device r;
default_random_engine e1(r());
uniform_real_distribution<float> probability_run(0, 1);

int num_attempts = 10000;
int length_of_walk = 100;

void runLoop(int num_attempts, int length_of_walk, bool isCorrelated, int initial_direction, float prob) {
	for (int i = 0; i < num_attempts; ++i) {
		Walker w = Walker(prob, isCorrelated);
		fprintf(fp, "%d,%d", i + 1, w.position);
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

		//inner loop
		for (int j = 1; j < length_of_walk; ++j) {
			w.Move(probability_run(e1));
			fprintf(fp, ",%d", w.position);
			average_walk[j + 1] += w.position;
		}
		fprintf(fp, "\n");
	}
}

void process_avg(char str[]) {
	fprintf(fp_avg, "%s", str);
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp_avg, ",%f", average_walk[i] / num_attempts);
		average_walk[i] = 0.0f;
	}
	fprintf(fp_avg, "\n");
}

int main()
{
	fp_avg = fopen("averages.csv", "w");
	fprintf(fp_avg, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp_avg, ",step %d", i);
		average_walk.push_back(0.0f);
	}
	fprintf(fp_avg, "\n");

	

	printf("Simple_Random_Walk_ProbRight=0.3\n");
	fp = fopen("Simple_Random_Walk_ProbRight=0.3.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 0, 0.3);
	process_avg("Simple_Random_Walk_ProbRight=0.3");
	fclose(fp);

	printf("Simple_Initial_Right_Random_Walk_ProbRight=0.3\n");
	fp = fopen("Simple_Initial_Right_Random_Walk_ProbRight=0.3.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 1, 0.3);
	process_avg("Simple_Initial_Right_Random_Walk_ProbRight=0.3");
	fclose(fp);

	printf("Correlated_Random_Walk_ProbTurn=0.3\n");
	fp = fopen("Correlated_Random_Walk_ProbTurn=0.3.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 0, 0.3);
	process_avg("Correlated_Random_Walk_ProbTurn=0.3");
	fclose(fp);

	printf("Correlated_Initial_Right_Random_Walk_ProbTurn=0.3\n");
	fp = fopen("Correlated_Initial_Right_Random_Walk_ProbTurn=0.3.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 1, 0.3);
	process_avg("Correlated_Initial_Right_Random_Walk_ProbTurn=0.3");
	fclose(fp);



	printf("Simple_Random_Walk_ProbRight=0.5\n");
	fp = fopen("Simple_Random_Walk_ProbRight=0.5.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk+1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 0, 0.5);
	process_avg("Simple_Random_Walk_ProbRight=0.5");
	fclose(fp);

	printf("Simple_Initial_Right_Random_Walk_ProbRight=0.5\n");
	fp = fopen("Simple_Initial_Right_Random_Walk_ProbRight=0.5.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 1, 0.5);
	process_avg("Simple_Initial_Right_Random_Walk_ProbRight=0.5");
	fclose(fp);

	printf("Correlated_Random_Walk_ProbTurn=0.5\n");
	fp = fopen("Correlated_Random_Walk_ProbTurn=0.5.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 0, 0.5);
	process_avg("Correlated_Random_Walk_ProbTurn=0.5");
	fclose(fp);

	printf("Correlated_Initial_Right_Random_Walk_ProbTurn=0.5\n");
	fp = fopen("Correlated_Initial_Right_Random_Walk_ProbTurn=0.5.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 1, 0.5);
	process_avg("Correlated_Initial_Right_Random_Walk_ProbTurn=0.5");
	fclose(fp);



	printf("Simple_Random_Walk_ProbRight=0.7\n");
	fp = fopen("Simple_Random_Walk_ProbRight=0.7.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 0, 0.7);
	process_avg("Simple_Random_Walk_ProbRight=0.7");
	fclose(fp);

	printf("Simple_Initial_Right_Random_Walk_ProbRight=0.7\n");
	fp = fopen("Simple_Initial_Right_Random_Walk_ProbRight=0.7.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, false, 1, 0.7);
	process_avg("Simple_Initial_Right_Random_Walk_ProbRight=0.7");
	fclose(fp);

	printf("Correlated_Random_Walk_ProbTurn=0.7\n");
	fp = fopen("Correlated_Random_Walk_ProbTurn=0.7.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 0, 0.7);
	process_avg("Correlated_Random_Walk_ProbTurn=0.7");
	fclose(fp);

	printf("Correlated_Initial_Right_Random_Walk_ProbTurn=0.7\n");
	fp = fopen("Correlated_Initial_Right_Random_Walk_ProbTurn=0.7.csv", "w");
	fprintf(fp, "attempt number");
	for (int i = 0; i < length_of_walk + 1; ++i) {
		fprintf(fp, ",step %d", i);
	}
	fprintf(fp, "\n");
	runLoop(num_attempts, length_of_walk, true, 1, 0.7);
	process_avg("Correlated_Initial_Right_Random_Walk_ProbTurn=0.7");
	fclose(fp);



	fclose(fp_avg);

	printf("Done");
	return 0;
}