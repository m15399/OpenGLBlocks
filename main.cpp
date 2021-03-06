
bool running = true;

int main(){

	g_window.Init();
	g_input.Init();
	g_shaders.Init();
	g_time.Init();
	g_primitives.Init();
	g_camera.Init();
	g_audio.Init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Select game
	g_game = new Game();
	g_game->Init();

	while(running){
		g_input.Update();
		g_time.Update();

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							g_window.Resize(event.window.data1, event.window.data2);
							break;
					}

				// TODO implement audio switching:
				// if ((event.type == SDL_AUDIODEVICEADDED && !event.adevice.iscapture) ||
				// 	(event.type == SDL_AUDIODEVICEREMOVED && !event.adevice.iscapture && event.adevice.which == device)) {
				// 	reopen_audio();
				// }
				// TODO there is also this check in the example:
				// (SDL_GetAudioDeviceStatus(device) != SDL_AUDIO_PLAYING)
		
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					g_input.UpdateKey(event.key);
					break;
				default:
					break;
			}
		}


		// Update
		{
			g_game->Update();

			g_camera.Update();
		}

		// Draw

		glClearColor(0, .25, .45, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		{
			g_game->Draw();

			g_window.Draw();
		}

		if(g_input.KeyPressed(SDL_SCANCODE_GRAVE)){
			g_globals.debug = !g_globals.debug;
			std::cout << "Debug = " << g_globals.debug << "\n";
		}
		if(g_input.KeyPressed(SDL_SCANCODE_F1)){
			g_window.ToggleFullscreen();
		}
		if(g_input.KeyPressed(SDL_SCANCODE_F2)){
			g_window.ToggleUnlockedFramerate();
		}
		if(g_input.KeyPressed(SDL_SCANCODE_ESCAPE)){
			running = false;
		}
	}

	SDL_Quit();
	return 0;
}
