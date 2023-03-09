#include "DebugHUD.h"
#include <string>


using namespace std;

DebugHUD* DebugHUD::mspInstance = nullptr;

DebugHUD* DebugHUD::getInstance()
{
	if (!mspInstance)
		mspInstance = new DebugHUD();

	return mspInstance;
}

void DebugHUD::cleanupInstnace()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

DebugHUD::DebugHUD()
{

}

DebugHUD::~DebugHUD()
{

}

void DebugHUD::addDebugValue(string valueName, int_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.i = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::Int;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(string valueName, float_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.f = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::Float;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(string valueName, string_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.s = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::String;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(string valueName, gs_int_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.gsi = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::GSInt;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(string valueName, gs_float_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.gsf = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::GSFloat;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(string valueName, gs_string_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.gss = getterFunc;
	getter.unionType = TrackedGetterFunction::getterFunctionType::GSString;

	mDebugFunctionMap.emplace(valueName, getter);
}

void DebugHUD::draw()
{
	float offsetAmount = 30.0f;
	float offset = GraphicsSystem::getInstance()->getDisplayHeight() - offsetAmount;
	for (unordered_map<string, TrackedGetterFunction>::iterator i = mDebugFunctionMap.begin();
		i != mDebugFunctionMap.end();
		i++, offset -= offsetAmount)
	{
		string output = i->first;
		Vector2D loc = Vector2D(0.0f, offset);

		switch (i->second.unionType)
		{

		case TrackedGetterFunction::Int:
			output += to_string(i->second.func.i());
			break;

		case TrackedGetterFunction::Float:
			output += to_string(i->second.func.f());
			break;

		case TrackedGetterFunction::String:
			output += i->second.func.s();
			break;

		case TrackedGetterFunction::GSInt:
			output += to_string((GraphicsSystem::getInstance()->*i->second.func.gsi)()); // This line of code is barf unreadable.....
			break;

		case TrackedGetterFunction::GSFloat:
			output += to_string((GraphicsSystem::getInstance()->*i->second.func.gsf)()); // This line of code is barf unreadable.....
			break;

		case TrackedGetterFunction::GSString:
			output += (GraphicsSystem::getInstance()->*i->second.func.gss)(); // This line of code is barf unreadable.....
			break;

		default:
			break;

		}

		GraphicsSystem::getInstance()->draw(output, "arial", "Text", loc, Vector3D(1.0f, 1.0f, 0.0f));
	}

	for (vector<string>::iterator i = mDebugValueMap.begin(); i != mDebugValueMap.end(); i++, offset -= offsetAmount)
	{
		Vector2D loc = Vector2D(0.0f, offset);
		GraphicsSystem::getInstance()->draw(*i, "arial", "Text", loc, Vector3D(1.0f, 1.0f, 0.0f));
	}

	mDebugValueMap.clear();
}

void DebugHUD::addDebugValue(std::string value)
{
	mDebugValueMap.push_back(value);
}