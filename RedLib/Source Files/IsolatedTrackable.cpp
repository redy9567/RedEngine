#include "IsolatedTrackable.h"
#include "MemoryTracker.h"

void* IsolatedTrackable::operator new(size_t size)
{
	void* ptr = malloc(size);
	MemoryTracker::getInstance()->addIsolatedAllocation(ptr, size);
	return ptr;
}

void IsolatedTrackable::operator delete(void* ptr)
{
	MemoryTracker::getInstance()->removeIsolatedAllocation(ptr);
	free(ptr);
}

void* IsolatedTrackable::operator new[](size_t size)
{
	void* ptr = malloc(size);
	MemoryTracker::getInstance()->addIsolatedAllocation(ptr, size);
	return ptr;
}

void IsolatedTrackable::operator delete[](void* ptr)
{
	MemoryTracker::getInstance()->removeIsolatedAllocation(ptr);
	free(ptr);
}