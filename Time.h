
#pragma once

#include "SDL.h"

// Delta time in sec
//
float dt();

// Time in sec
//
double time();


class Time {
public:

	static constexpr uint64_t fpsMeasurementIntervalMs = 500;

	uint64_t framesThisInterval;
	uint64_t time;
	uint64_t lastTime;
	uint64_t fps;

	uint64_t dt;


	void Init();
	void Update();

};

extern Time g_time;