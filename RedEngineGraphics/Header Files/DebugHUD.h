#pragma once
#include "Trackable.h"
#include <unordered_map>

class DebugHUD : public Trackable
{
public:
	friend class GraphicsSystem;

	typedef int (*int_getter_function)(void);
	typedef float (*float_getter_function)(void);

	union getter_function
	{
		int_getter_function i;
		float_getter_function f;
	};

	struct TrackedGetterFunction
	{
		enum getterFunctionType
		{
			Int,
			Float
		};

		getterFunctionType unionType;
		getter_function func;
	};

	static DebugHUD* getInstance();
	static void cleanupInstnace();

	DebugHUD();
	~DebugHUD();

	void addDebugValue(std::string valueName, int_getter_function getterFunc);
	void addDebugValue(std::string valueName, float_getter_function getterFunc);

private:
	void draw();

	std::unordered_map<std::string, TrackedGetterFunction> mDebugMap;

	static DebugHUD* mspInstance;
};