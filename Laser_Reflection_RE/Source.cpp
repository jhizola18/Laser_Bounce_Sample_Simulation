#include "WindowHandler.h"
#include "Simulation.h"

const int W_Window = 750;
const int H_Window = 750;
const int FPS_Window = 74;
std::string T_Window = "Vector Reflection Simulation";


WindowHandler window{ W_Window, H_Window, FPS_Window, T_Window };

Simulation Laser_Simulation = Simulation();


int main() {

	while (!window.isWindowClose()) {
		Laser_Simulation.MainSimulation();
		Laser_Simulation.MovementSimulation();
		BeginDrawing();
		ClearBackground(BLACK);
		Laser_Simulation.DrawSimulation();
		EndDrawing();
	}

}