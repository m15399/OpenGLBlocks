
Camera g_camera;

void Camera::Init(){
	CenterOn(glm::vec3(0, 0, 0), 10);
}

void Camera::Update(){
	float cameraSpeed = .5f;
	float rotSpeed = .8f;
	float voSpeed = .8f;


	if(g_input.KeyDown(SDL_SCANCODE_I))
		cameraDistance *= (1 - cameraSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_K))
		cameraDistance *= (1 + cameraSpeed * dt());

	switch(mode){
		case Mode::Targetted:
		{
			
			if(g_input.KeyDown(SDL_SCANCODE_O))
				offsetY += (voSpeed * dt());
			if(g_input.KeyDown(SDL_SCANCODE_U))
				offsetY -= (voSpeed * dt());
			if(g_input.KeyDown(SDL_SCANCODE_J))
				rotationX -= (rotSpeed * dt());
			if(g_input.KeyDown(SDL_SCANCODE_L))
				rotationX += (rotSpeed * dt());

		}
		break;
		case Mode::TopDown:
		{
		}
		break;
	}
	

	if(g_input.KeyPressed(SDL_SCANCODE_0)){
		cameraDistance = defaultCameraDistance;
		offsetY = 0;
		rotationX = 0;
	}

	g_camera.CenterOn(center, cameraDistance);
}

void Camera::CenterOn(const glm::vec3 &point, float distance){
	if(distance == 0)
		distance = cameraDistance;

	cameraDistance = distance;
	up = glm::vec3(0, 0, 1);
	center = point;

	switch(mode){
		case Mode::Targetted:
		{
			eye = glm::vec3(-distance, -distance, distance * (1.25f + offsetY) );
			eye = glm::rotate(eye, rotationX, glm::vec3(0, 0, 1));
		}
		break;
		case Mode::TopDown:
		{
			eye = glm::vec3(0, 0, cameraDistance);
			up = glm::vec3(0, 1, 0);
		}
		break;
	}
	eye += point;

	dirtyMatrix = true;
}

glm::mat4 Camera::GetViewProjMatrix(){
	if(dirtyMatrix){
		viewMatrix = glm::lookAt(eye, center, up);

		float aspect = (float) g_window.width / g_window.height;

		switch(mode){
			case Mode::Targetted:
			{
				projMatrix = glm::perspective(glm::radians(30.0f), aspect, 1.0f, 500.f);
			}
			break;
			case Mode::TopDown:
			{
				float height = cameraDistance;
				float width = height * aspect;
				projMatrix = glm::ortho(-width/2, width/2, -height/2, height/2, .1f, 1000.0f);
			}
			break;
		}

		viewProjMatrix = projMatrix * viewMatrix;
		dirtyMatrix = false;
	}
	return viewProjMatrix;
}
