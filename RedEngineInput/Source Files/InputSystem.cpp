#include "InputSystem.h"
#include "GraphicsSystem.h"
#include "../../glfw-3.3.8/include/GLFW/glfw3.h"
#include "EventSystem.h"
#include <MouseEvent.h>
#include <KeyboardEvent.h>
#include <AxisEvent.h>

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

void _scrollCallback(double xOffset, double yOffset)
{
	InputSystem::getInstance()->updateScroll(xOffset, yOffset);
}

InputSystem::InputSystem()
{
	GraphicsSystem::getInstance()->_imSetScrollCallback(_scrollCallback, GraphicsSystem::GraphicsSystemIMKey());
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

bool InputSystem::getMouseButton(MouseAction button)
{
	return GraphicsSystem::getInstance()->_imGetMouseButton((unsigned int)button, GraphicsSystem::GraphicsSystemIMKey());
}

Vector2D InputSystem::getMousePosition()
{
	return GraphicsSystem::getInstance()->_imGetMousePosition(GraphicsSystem::GraphicsSystemIMKey());
}

void InputSystem::update()
{
	
	EventSystem* es = EventSystem::getInstance();
	Vector2D mousePos = getMousePosition();

	//Left clicks
	if (getMouseButtonDown(MouseAction::LeftClick))
	{
		MouseEvent mouseEvent(MouseAction::LeftClick, ButtonState::Down, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButtonUp(MouseAction::LeftClick))
	{
		MouseEvent mouseEvent(MouseAction::LeftClick, ButtonState::Up, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButton(MouseAction::LeftClick))
	{
		MouseEvent mouseEvent(MouseAction::LeftClick, ButtonState::Hold, mousePos);
		es->fireEvent(mouseEvent);
	}

	//Right clicks
	if (getMouseButtonDown(MouseAction::RightClick))
	{
		MouseEvent mouseEvent(MouseAction::RightClick, ButtonState::Down, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButtonUp(MouseAction::RightClick))
	{
		MouseEvent mouseEvent(MouseAction::RightClick, ButtonState::Up, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButton(MouseAction::RightClick))
	{
		MouseEvent mouseEvent(MouseAction::RightClick, ButtonState::Hold, mousePos);
		es->fireEvent(mouseEvent);
	}


	//Middle clicks
	if (getMouseButtonDown(MouseAction::MiddleClick))
	{
		MouseEvent mouseEvent(MouseAction::MiddleClick, ButtonState::Down, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButtonUp(MouseAction::MiddleClick))
	{
		MouseEvent mouseEvent(MouseAction::MiddleClick, ButtonState::Up, mousePos);
		es->fireEvent(mouseEvent);
	}
	else if (getMouseButton(MouseAction::MiddleClick))
	{
		MouseEvent mouseEvent(MouseAction::MiddleClick, ButtonState::Hold, mousePos);
		es->fireEvent(mouseEvent);
	}

	//Mouse Moves
	mousePos = getMousePosition();
	if (mMousePos != mousePos)
	{
		MouseEvent mouseEvent(MouseAction::Move, ButtonState::None, mousePos);
		es->fireEvent(mouseEvent);
	}

	//Keyboard Events
	getKeyboardState();

	mLeftClick = getMouseButton(MouseAction::LeftClick);
	mRightClick = getMouseButton(MouseAction::RightClick);
	mMiddleClick = getMouseButton(MouseAction::MiddleClick);
	mMousePos = mousePos;

	if (mScrollXOffset || mScrollYOffset)
	{
		MouseEvent mouseEvent(MouseAction::Scroll, ButtonState::None, mousePos, Vector2D(mScrollXOffset, mScrollYOffset));
		es->fireEvent(mouseEvent);

		mScrollXOffset = 0.0;
		mScrollYOffset = 0.0;
	}
}

bool InputSystem::getMouseButtonDown(MouseAction button)
{
	switch (button)
	{
	case MouseAction::LeftClick:
		return !mLeftClick && getMouseButton(button);
		break;
	case MouseAction::RightClick:
		return !mRightClick && getMouseButton(button);
		break;
	case MouseAction::MiddleClick:
		return !mMiddleClick && getMouseButton(button);
		break;
	default:
		return false;
		break;
	}
}

bool InputSystem::getMouseButtonUp(MouseAction button)
{
	switch (button)
	{
	case MouseAction::LeftClick:
		return mLeftClick && !getMouseButton(button);
		break;
	case MouseAction::RightClick:
		return mRightClick && !getMouseButton(button);
		break;
	case MouseAction::MiddleClick:
		return mMiddleClick && !getMouseButton(button);
		break;
	default:
		return false;
		break;
	}
}

void InputSystem::getKeyboardState()
{
	EventSystem* es = EventSystem::getInstance();

	for (KeyCode i = KeyCode::Esc; i < KeyCode::MAX_KEYS; i = (KeyCode)((int)i + 1))
	{

		bool currentState = getKey(i);

		vector<KeyCode>::iterator lastState = find(mPressedKeys.begin(), mPressedKeys.end(), i);

		if (currentState) //Currently Pressed
		{
			if (lastState != mPressedKeys.end()) //Pressed last frame
			{
				KeyboardEvent keyEvent(i, KeyState::Hold);
				es->fireEvent(keyEvent);
			}
			else //Wasn't pressed last frame
			{
				KeyboardEvent keyEvent(i, KeyState::Down);
				es->fireEvent(keyEvent);

				mPressedKeys.push_back(i);
			}
		}
		else //Not currently pressed
		{
			if (lastState != mPressedKeys.end()) //Pressed last frame
			{
				KeyboardEvent keyEvent(i, KeyState::Up);
				es->fireEvent(keyEvent);

				mPressedKeys.erase(lastState);
			}
		}

	}

	//Determine axis
	Vector2D axis;

	vector<KeyCode>::iterator op1 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::D);
	vector<KeyCode>::iterator op2 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::Right);
	
	if (op1 != mPressedKeys.end() || op2 != mPressedKeys.end())
	{
		axis.setX(1.0f);
	}


	op1 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::W);
	op2 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::Up);

	if (op1 != mPressedKeys.end() || op2 != mPressedKeys.end())
	{
		axis.setY(1.0f);
	}


	op1 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::A);
	op2 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::Left);

	if (op1 != mPressedKeys.end() || op2 != mPressedKeys.end())
	{
		axis.setX(axis.getX() - 1.0f); //Subtract here to cancel out right press, rather than override
	}


	op1 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::S);
	op2 = find(mPressedKeys.begin(), mPressedKeys.end(), KeyCode::Down);

	if (op1 != mPressedKeys.end() || op2 != mPressedKeys.end())
	{
		axis.setY(axis.getY() - 1.0f); //Subtract here to cancel out up press, rather than override
	}


	//Normalize if we have both axis
	if (axis.getX() != 0.0f && axis.getY() != 0.0f)
	{
		axis.normalize();
	}

	if (mAxis != axis) //Only update if axis are different than last frame
	{
		mAxis = axis;

		AxisEvent ev(axis);
		es->fireEvent(ev);
	}
}

void InputSystem::updateScroll(double xOffset, double yOffset)
{
	mScrollXOffset = xOffset;
	mScrollYOffset = yOffset;
}