
#pragma once

float Random(float low, float high);
int Random(int low, int high);

template <typename T>
T Clamp(T v, T a, T b){
	if(v < a)
		return a;
	if(v > b)
		return b;
	return v;
}

template <typename T>
T Lerp(T a, T b, float t){
	return (T)((b - a) * t + a);
}
