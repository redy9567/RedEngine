//#pragma comment(lib, "raylib.lib")

//#include "raylib-cpp.hpp"
#include <raylib-cpp.hpp>
using namespace std;
using namespace raylib;

int main()
{

	int screenWidth = 800;
	int screenHeight = 450;

	raylib::Window w(screenWidth, screenHeight, "raylib-cpp - basic window");
	raylib::Texture logo("raylib_logo.png");
	SetTargetFPS(60);

	while (!w.ShouldClose())
	{
		BeginDrawing();

		raylib::Color::RayWhite.ClearBackground();

		DrawText("Congrats! You created your first window!", 190, 200, 20, ::LIGHTGRAY);

		// Object methods.
		logo.Draw(
			screenWidth / 2 - logo.GetWidth() / 2,
			screenHeight / 2 - logo.GetHeight() / 2);

		EndDrawing();
	}

	// UnloadTexture() and CloseWindow() are called automatically.

	return 0;
}