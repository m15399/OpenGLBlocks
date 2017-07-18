
#include <cstring>

#include "Input.h"

Input g_input;

void Input::Init(){

}

bool Input::KeyPressed(SDL_Scancode scancode){
	return keysPressed[scancode];
}

bool Input::KeyDown(SDL_Scancode scancode){
	return keysDown[scancode];
}


void Input::Update(){
	memset(keysPressed, 0, KeyArraySize * sizeof(bool));
}

void Input::UpdateKey(SDL_KeyboardEvent& e){

	int index = e.keysym.scancode;

	if(e.state == SDL_PRESSED){
		if(!e.repeat){
			keysPressed[index] = true;
			keysDown[index] = true;
		}
	} else {
		keysDown[index] = false;
	}

}

