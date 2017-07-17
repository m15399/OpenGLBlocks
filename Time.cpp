
#include <chrono>
#include <iostream>

#include "Time.h"

Time g_time;

uint64_t Millis(){
	uint64_t milliseconds_since_epoch = 
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	return milliseconds_since_epoch;
}

void Time::Init(){
	time = Millis();
	lastTime = time - 1;
	fps = 0;
	framesThisInterval = 0;
}

void Time::Update(){
	lastTime = time;
	time = Millis();

	framesThisInterval++;

	if(time / fpsMeasurementIntervalMs > lastTime / fpsMeasurementIntervalMs){
		fps = framesThisInterval * 1000 / fpsMeasurementIntervalMs; 
		framesThisInterval = 0;

		std::cout << "FPS: " << fps << "\n";
	}
}

float Time::GetFps(){
	return 0;
}


