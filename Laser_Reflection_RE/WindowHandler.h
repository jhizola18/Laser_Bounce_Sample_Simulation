#include "raylib.h"
#include <String>
#include <Assert.h>


class WindowHandler {
public:
	WindowHandler(int width, int height, int fps, std::string title);
	~WindowHandler()noexcept;
	bool isWindowClose();

};


