#ifndef INPUT_H
#define INPUT_H

#include "SDLBackend.h"
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

class Input
{
public:

	enum {
		LEFT_MOUSE = 1,
		MIDDLE_MOUSE = 2,
		RIGHT_MOUSE = 3,
		MOUSE_WHEEL_UP = 4,
		MOUSE_WHEEL_DOWN = 5
	};

	// TODO: ADD ENUMS FOR MOUSE AND KEYBOARD BUTTONS
	enum {
		KEY_A = 4,
		KEY_B = 5,
		KEY_C = 6,
		KEY_D = 7,
		KEY_E = 8,
		KEY_F = 9,
		KEY_G = 10,
		KEY_H = 11,
		KEY_I = 12,
		KEY_J = 13,
		KEY_K = 14,
		KEY_L = 15,
		KEY_M = 16,
		KEY_N = 17,
		KEY_O = 18,
		KEY_P = 19,
		KEY_Q = 20,
		KEY_R = 21,
		KEY_S = 22,
		KEY_T = 23,
		KEY_U = 24,
		KEY_V = 25,
		KEY_W = 26,
		KEY_X = 27,
		KEY_Y = 28,
		KEY_Z = 29,

		KEY_1 = 30,
		KEY_2 = 31,
		KEY_3 = 32,
		KEY_4 = 33,
		KEY_5 = 34,
		KEY_6 = 35,
		KEY_7 = 36,
		KEY_8 = 37,
		KEY_9 = 38,
		KEY_0 = 39,

		KEY_RETURN = 40,
		KEY_ESCAPE = 41,
		KEY_BACKSPACE = 42,
		KEY_TAB = 43,
		KEY_SPACE = 44
	};

	static void Update();

	static bool GetKey(int keycode);
	static bool GetKeyPressed(int keycode);
	static bool GetKeyReleased(int keycode);

	static bool GetMouse(int mousebutton);
	static bool GetMousePressed(int mousebutton);
	static bool GetMouseReleased(int mousebutton);
	static glm::vec2 GetMousePosition();

	static void SetCursor(bool visible);
	static void SetMousePosition(glm::vec2 pos);
};

#endif