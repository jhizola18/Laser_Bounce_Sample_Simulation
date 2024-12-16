#include "WindowHandler.h"
const int W_Window = 750;
const int H_Window = 750;
const int FPS_Window = 74;
std::string T_Window = "Vector Reflection Simulation";


WindowHandler window{ W_Window, H_Window, FPS_Window, T_Window };

//create Laser manager class to handle the creation of lasers

int main() {

	while (!window.isWindowClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

}