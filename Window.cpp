
Window g_window;

void Window::Init(){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 );

	uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

#if 0
 	flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif

	if(fullscreen){
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		flags);

	glcontext = SDL_GL_CreateContext(window);

	lockedFramerate = !lockedFramerate;
	ToggleUnlockedFramerate();

	Resize(width, height);
}

void Window::Resize(int newWidth, int newHeight){
	width = newWidth;
	height = newHeight;

	// Actual pixels are different if using high dpi
	int pxWidth, pxHeight; 
	SDL_GL_GetDrawableSize(window, &pxWidth, &pxHeight);

	std::cout << "Window size: " << width << " x " << height << 
		" (pxSize: " << pxWidth << " x " << pxHeight << ")\n";

	glViewport(0, 0, pxWidth, pxHeight);
}


void Window::ToggleFullscreen(){
	fullscreen = !fullscreen;
	std::cout << "Fullscreen: " << fullscreen << "\n";

	uint32_t flags = 0;
	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;

		// SDL_DisplayMode display;
		// SDL_GetCurrentDisplayMode(0, &display);
		// std::cout << display.w << " ---- " << display.h << "\n";
	}
	SDL_SetWindowFullscreen(window, flags);
}

void Window::ToggleUnlockedFramerate(){
	lockedFramerate = !lockedFramerate;
	std::cout << "Locked framerate: " << lockedFramerate << "\n";

	if(lockedFramerate)
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);
}

void Window::Draw(){
	SDL_GL_SwapWindow(window);
}
