#pragma once
#include <iostream>

class Trackable
{
public:
	Trackable() {}

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	void* operator new[](std::size_t size);
	void operator delete[](void* ptr);

	//Placement new
	void* operator new(std::size_t size, void* ptr) { return ptr; }
	void operator delete(void* ptr1, void* ptr2) {}
	void* operator new[](std::size_t size, void* ptr) { return ptr; }
	void operator delete[](void* ptr1, void* ptr2) {}

private:

};
