//Inspired by Dean Lawson, Champlain College

#pragma once

class Trackable
{
public:
	Trackable() {}

	void* operator new(size_t size);
	void operator delete(void* ptr);
	void* operator new[](size_t size);
	void operator delete[](void* ptr);
};
