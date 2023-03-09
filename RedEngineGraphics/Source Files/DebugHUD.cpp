#include "DebugHUD.h"
#include <string>
#include "GraphicsSystem.h"

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

void DebugHUD::addDebugValue(std::string valueName, int_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.i = getterFunc;

	mDebugMap.emplace(valueName, getter);
}

void DebugHUD::addDebugValue(std::string valueName, float_getter_function getterFunc)
{
	TrackedGetterFunction getter;

	getter.func.f = getterFunc;

	mDebugMap.emplace(valueName, getter);
}

void DebugHUD::draw()
{
	float offset = 0.0f;
	for (unordered_map<string, TrackedGetterFunction>::iterator i = mDebugMap.begin();
		i != mDebugMap.end();
		i++, offset += 80.0f)
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

		}

		//GraphicsSystem::getInstance()->draw(output, loc);
	}
}