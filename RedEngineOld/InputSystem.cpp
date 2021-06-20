#include "InputSystem.h"
#include "raylib.hpp"

InputSystem::InputSystem()
{
	
}

InputSystem::~InputSystem()
{

}

bool InputSystem::getKey(KeyCode key)
{
	return IsKeyDown(key);
}

bool InputSystem::getKeyDown(KeyCode key)
{
	return IsKeyPressed(key);
}

bool InputSystem::getKeyUp(KeyCode key)
{
	return IsKeyReleased(key);
}

bool InputSystem::getMouseButtonDown(int button)
{
	std::cout << "Y";kjjkjkj
	return IsMouseButtonPressed(button);
}

bool InputSystem::getMouseButtonUp(int button)
{
	return IsMouseButtonReleased(button);
}

bool InputSystem::getMouseButton(int button)
{
	return IsMouseButtonDown(button);
}

int InputSystem::getMouseX()
{
	return GetMouseX();
}

int InputSystem::getMouseY()
{
	return GetMouseY();
}

Vector2D InputSystem::getMousePosition()
{
	return Vector2D(GetMouseX(), getMouseY());
}