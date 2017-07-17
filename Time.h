
#pragma once

#include <stdint.h>

class Time {
public:

	static constexpr uint64_t fpsMeasurementIntervalMs = 500;

	uint64_t framesThisInterval;
	uint64_t time;
	uint64_t lastTime;
	uint64_t fps;


	void Init();
	void Update();

	float GetFps();

};

extern Time g_time;