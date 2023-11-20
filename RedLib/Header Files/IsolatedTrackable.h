//Inspired by Dean Lawson, Champlain College

#pragma once
#include <cstdlib>

class IsolatedTrackable
{
public:
	IsolatedTrackable() {}

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	void* operator new[](std::size_t size);
	void operator delete[](void* ptr);
};
