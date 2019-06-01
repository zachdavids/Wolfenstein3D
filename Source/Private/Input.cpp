#include "Input.h"



void Input::Update()
{
	/*
	// Clears Keyboard Arrays
	for (int i = 0; i < KEYBOARD_KEYS; i++) {
		keyboard_pressed[i] = false;
		keyboard_released[i] = false;
	}

	// Clears Mouse Arrays
	for (int i = 0; i < MOUSE_BUTTONS; i++) {
		mouse_pressed[i] = false;
		mouse_released[i] = false;
	}

	// Event listener
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			SDLSetIsCloseRequested(true);
		}
		// Keyboard Key Pressed
		if (event.type == SDL_KEYDOWN)
		{
			int value = event.key.keysym.scancode;

			keyboard_input[value] = true;
			keyboard_pressed[value] = true;
		}
		// Keyboard Key Released
		if (event.type == SDL_KEYUP)
		{
			int value = event.key.keysym.scancode;

			keyboard_input[value] = false;
			keyboard_pressed[value] = true;
		}
		// Mouse Motion
		if (event.type == SDL_MOUSEMOTION)
		{
			mouse_x = event.motion.x;
			mouse_y = event.motion.y;
		}
		// Mouse Button Pressed
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = event.button.button;

			mouse_input[value] = true;
			mouse_pressed[value] = true;
		}
		// Mouse Button Released
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			int value = event.button.button;

			mouse_input[value] = false;
			mouse_released[value] = true;
		}
	}
	*/
}

bool Input::GetKey(int keycode)
{
	//return keyboard_input[keycode];
	return false;
}

bool Input::GetKeyPressed(int keycode)
{
	//return keyboard_pressed[keycode];
	return false;
}

bool Input::GetKeyReleased(int keycode)
{
	//return keyboard_released[keycode];
	return false;
}

bool Input::GetMouse(int mousebutton)
{
	//return mouse_input[mousebutton];
	return false;
}

bool Input::GetMousePressed(int mousebutton)
{
	//return mouse_pressed[mousebutton];
	return false;
}

bool Input::GetMouseReleased(int mousebutton)
{
	//return mouse_released[mousebutton];
	return false;
}

glm::vec2 Input::GetMousePosition()
{
	//glm::vec2 position(mouse_x, mouse_y);
	//return position;
	return glm::vec2(1.0);
}

void Input::SetMousePosition(glm::vec2 position)
{
	//SDLSetMousePosition((int)position.x, (int)position.y);
}
