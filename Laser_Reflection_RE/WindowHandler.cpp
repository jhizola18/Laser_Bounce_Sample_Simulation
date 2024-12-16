#include "WindowHandler.h"

WindowHandler::WindowHandler(int width, int height, int fps, std::string title)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);
}

WindowHandler::~WindowHandler()
{
	assert(GetWindowHandle());
	CloseWindow();
}

bool WindowHandler::isWindowClose()
{
	return WindowShouldClose();
}

