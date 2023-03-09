#pragma once
#include "Trackable.h"
#include <unordered_map>
#include "GraphicsSystem.h"
#include <string>

class DebugHUD : public Trackable
{
public:
	friend class GraphicsSystem;

	static DebugHUD* getInstance();
	static void cleanupInstnace();

private:

	typedef int (GraphicsSystem::*gs_int_getter_function)(void);
	typedef float (GraphicsSystem::*gs_float_getter_function)(void);
	typedef std::string(GraphicsSystem::* gs_string_getter_function)(void);
	typedef int (*int_getter_function)(void);
	typedef float (*float_getter_function)(void);
	typedef std::string(*string_getter_function)(void);

	union getter_function
	{
		int_getter_function i;
		float_getter_function f;
		string_getter_function s;
		gs_int_getter_function gsi;
		gs_float_getter_function gsf;
		gs_string_getter_function gss;
	};

	struct TrackedGetterFunction
	{
		enum getterFunctionType
		{
			Int,
			Float,
			String,
			GSInt,
			GSFloat,
			GSString
		};

		getterFunctionType unionType;
		getter_function func;
	};

	DebugHUD();
	~DebugHUD();

	void addDebugValue(std::string valueName, int_getter_function getterFunc);
	void addDebugValue(std::string valueName, float_getter_function getterFunc);
	void addDebugValue(std::string valueName, string_getter_function getterFunc);
	void addDebugValue(std::string valueName, gs_int_getter_function getterFunc);
	void addDebugValue(std::string valueName, gs_float_getter_function getterFunc);
	void addDebugValue(std::string valueName, gs_string_getter_function getterFunc);

	void addDebugValue(std::string value);

	void draw();

	std::unordered_map<std::string, TrackedGetterFunction> mDebugFunctionMap;
	std::vector<std::string> mDebugValueMap;

	static DebugHUD* mspInstance;
};