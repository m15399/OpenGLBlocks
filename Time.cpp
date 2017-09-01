
Time g_time;

float dt(){
	return g_time.dt / 1000.f;
}

uint64_t Millis(){
	uint64_t milliseconds_since_epoch = 
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	return milliseconds_since_epoch;
}

void Time::Init(){
	time = Millis();
	lastTime = time - 1;
	dt = time - lastTime;
	fps = 0;
	framesThisInterval = 0;
}

void Time::Update(){
	lastTime = time;
	time = Millis();

	dt = time - lastTime;

	framesThisInterval++;

	if(time / fpsMeasurementIntervalMs > lastTime / fpsMeasurementIntervalMs){
		fps = framesThisInterval * 1000 / fpsMeasurementIntervalMs; 
		framesThisInterval = 0;

		if(g_globals.debug){
			std::cout << "FPS: " << fps << "\n";
		}
	}
}


