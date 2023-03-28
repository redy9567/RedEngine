#include "InputSystem.h"
#include "GraphicsSystem.h"
#include "../../glfw-3.3.8/include/GLFW/glfw3.h"

using namespace std;

InputSystem* InputSystem::mspInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
	if (!mspInstance)
		mspInstance = new InputSystem();

	return mspInstance;
}

void InputSystem::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

bool InputSystem::getKey(KeyCode key)
{
	unsigned int glfwKey = 0;

	//GLFW Key Definitions
	switch (key)
	{
	case KeyCode::Esc:
		glfwKey = 256;
		break;

	case KeyCode::F1:
		glfwKey = 290;
		break;

	case KeyCode::F2:
		glfwKey = 291;
		break;

	case KeyCode::F3:
		glfwKey = 292;
		break;

	case KeyCode::F4:
		glfwKey = 293;
		break;

	case KeyCode::F5:
		glfwKey = 294;
		break;

	case KeyCode::F6:
		glfwKey = 295;
		break;

	case KeyCode::F7:
		glfwKey = 296;
		break;

	case KeyCode::F8:
		glfwKey = 297;
		break;

	case KeyCode::F9:
		glfwKey = 298;
		break;

	case KeyCode::F10:
		glfwKey = 299;
		break;

	case KeyCode::F11:
		glfwKey = 300;
		break;

	case KeyCode::F12:
		glfwKey = 301;
		break;

	case KeyCode::Tilde:
		glfwKey = 96;
		break;

	case KeyCode::Num0:
		glfwKey = 48;
		break;

	case KeyCode::Num1:
		glfwKey = 49;
		break;

	case KeyCode::Num2:
		glfwKey = 50;
		break;

	case KeyCode::Num3:
		glfwKey = 51;
		break;

	case KeyCode::Num4:
		glfwKey = 52;
		break;

	case KeyCode::Num5:
		glfwKey = 53;
		break;

	case KeyCode::Num6:
		glfwKey = 54;
		break;

	case KeyCode::Num7:
		glfwKey = 55;
		break;

	case KeyCode::Num8:
		glfwKey = 56;
		break;

	case KeyCode::Num9:
		glfwKey = 57;
		break;

	case KeyCode::Minus:
		glfwKey = 45;
		break;

	case KeyCode::Equals:
		glfwKey = 61;
		break;

	case KeyCode::Backspace:
		glfwKey = 259;
		break;

	case KeyCode::Tab:
		glfwKey = 258;
		break;

	case KeyCode::A:
		glfwKey = 65;
		break;

	case KeyCode::B:
		glfwKey = 66;
		break;

	case KeyCode::C:
		glfwKey = 67;
		break;

	case KeyCode::D:
		glfwKey = 68;
		break;

	case KeyCode::E:
		glfwKey = 69;
		break;

	case KeyCode::F:
		glfwKey = 70;
		break;

	case KeyCode::G:
		glfwKey = 71;
		break;

	case KeyCode::H:
		glfwKey = 72;
		break;

	case KeyCode::I:
		glfwKey = 73;
		break;

	case KeyCode::J:
		glfwKey = 74;
		break;

	case KeyCode::K:
		glfwKey = 75;
		break;

	case KeyCode::L:
		glfwKey = 76;
		break;

	case KeyCode::M:
		glfwKey = 77;
		break;

	case KeyCode::N:
		glfwKey = 78;
		break;

	case KeyCode::O:
		glfwKey = 79;
		break;

	case KeyCode::P:
		glfwKey = 80;
		break;

	case KeyCode::Q:
		glfwKey = 81;
		break;

	case KeyCode::R:
		glfwKey = 82;
		break;

	case KeyCode::S:
		glfwKey = 83;
		break;

	case KeyCode::T:
		glfwKey = 84;
		break;

	case KeyCode::U:
		glfwKey = 85;
		break;

	case KeyCode::V:
		glfwKey = 86;
		break;

	case KeyCode::W:
		glfwKey = 87;
		break;

	case KeyCode::X:
		glfwKey = 88;
		break;

	case KeyCode::Y:
		glfwKey = 89;
		break;

	case KeyCode::Z:
		glfwKey = 90;
		break;

	case KeyCode::LeftBracket:
		glfwKey = 91;
		break;

	case KeyCode::RightBracket:
		glfwKey = 93;
		break;

	case KeyCode::Backslash:
		glfwKey = 92;
		break;

	case KeyCode::CapsLock:
		glfwKey = 280;
		break;

	case KeyCode::Semicolon:
		glfwKey = 59;
		break;

	case KeyCode::Apostrophe:
		glfwKey = 39;
		break;

	case KeyCode::Enter:
		glfwKey = 257;
		break;

	case KeyCode::LeftShift:
		glfwKey = 340;
		break;

	case KeyCode::Comma:
		glfwKey = 44;
		break;

	case KeyCode::Period:
		glfwKey = 46;
		break;

	case KeyCode::Slash:
		glfwKey = 47;
		break;

	case KeyCode::RightShift:
		glfwKey = 344;
		break;

	case KeyCode::LeftControl:
		glfwKey = 341;
		break;

	case KeyCode::LeftAlt:
		glfwKey = 342;
		break;

	case KeyCode::Space:
		glfwKey = 32;
		break;

	case KeyCode::RightAlt:
		glfwKey = 346;
		break;

	case KeyCode::RightControl:
		glfwKey = 345;
		break;

	case KeyCode::PrintScreen:
		glfwKey = 283;
		break;

	case KeyCode::ScrollLock:
		glfwKey = 281;
		break;

	case KeyCode::Pause:
		glfwKey = 284;
		break;

	case KeyCode::Insert:
		glfwKey = 260;
		break;

	case KeyCode::Home:
		glfwKey = 268;
		break;

	case KeyCode::PageUp:
		glfwKey = 266;
		break;

	case KeyCode::Delete:
		glfwKey = 261;
		break;

	case KeyCode::End:
		glfwKey = 269;
		break;

	case KeyCode::PageDown:
		glfwKey = 267;
		break;

	case KeyCode::Up:
		glfwKey = 265;
		break;

	case KeyCode::Left:
		glfwKey = 263;
		break;

	case KeyCode::Down:
		glfwKey = 264;
		break;

	case KeyCode::Right:
		glfwKey = 262;
		break;

	default:
		return false;
	}

	return GraphicsSystem::getInstance()->_imGetKey(glfwKey, GraphicsSystem::GraphicsSystemIMKey());
}

bool InputSystem::getMouseButton(MouseButton button)
{
	return GraphicsSystem::getInstance()->_imGetMouseButton((unsigned int)button, GraphicsSystem::GraphicsSystemIMKey());
}

Vector2D InputSystem::getMousePosition()
{
	return GraphicsSystem::getInstance()->_imGetMousePosition(GraphicsSystem::GraphicsSystemIMKey());
}