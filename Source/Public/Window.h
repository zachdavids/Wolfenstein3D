#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "SDLBackend.h"

class Window
{
public:

	static void Create(float width, float height, const std::string& title);
	static void Destroy();
	static void Render();
	static bool CloseRequested();

	static float GetWidth() { return width_; };
	static float GetHeight() { return height_; };
	static const std::string& GetTitle() { return title_; };
	static void SetFullScreen(bool value);

private:

	static float width_;
	static float height_;
	static std::string title_;
};

#endif