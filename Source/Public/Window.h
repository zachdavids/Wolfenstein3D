#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glew.h>
#include <SDL.h>
#include "SDLBackend.h"

class Window
{
public:

	static void Create(int width, int height, const std::string& title);
	static void Destroy();
	static void Render();
	static bool CloseRequested();

	static int GetWidth() { return width_; };
	static int GetHeight() { return height_; };
	static const std::string& GetTitle() { return title_; };
	static void SetFullScreen(bool value);

private:

	static int width_;
	static int height_;
	static std::string title_;
};

#endif