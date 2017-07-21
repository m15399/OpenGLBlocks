
#pragma once

#include <stdint.h>

// Delta time in sec
//
float dt();

class Time {
public:

	static constexpr uint64_t fpsMeasurementIntervalMs = 1000;

	uint64_t framesThisInterval;
	uint64_t time;
	uint64_t lastTime;
	uint64_t fps;

	uint64_t dt;


	void Init();
	void Update();

	float GetFps();

};

extern Time g_time;