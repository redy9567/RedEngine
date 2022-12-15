#pragma once
#include "Trackable.h"

class InputSystem : public Trackable
{

public:
	enum class KeyCode
	{
		Esc,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		
		Tilde,

		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,

		Minus,
		Equals,
		Backspace,
		
		Tab,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		LeftBracket,
		RightBracket,
		Backslash,

		CapsLock,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Semicolon,
		Apostrophe,
		Enter,

		LeftShift,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		Period,
		Slash,
		RightShift,

		LeftControl,
		LeftAlt,
		Space,
		RightAlt,
		RightControl,

		PrintScreen,
		ScrollLock,
		Pause,
		
		Insert,
		Home,
		PageUp,

		Delete,
		End,
		PageDown,

		Up,
		Down,
		Left,
		Right

	};

	static InputSystem* getInstance();
	static void cleanupInstance();

	bool getKey(KeyCode);

private:
	static InputSystem* mspInstance;

};