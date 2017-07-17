
#include <cstdlib>

#include "Utils.h"

float Random(float low, float high){
	int randInt = rand();
	float randFloat = randInt / (float) RAND_MAX;
	return randFloat * (high - low) + low;
}

int Random(int low, int high){
	int randInt = rand();
	return (randInt % (high - low)) + low;
}
