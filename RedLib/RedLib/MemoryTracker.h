#pragma once
#include <iostream>
#include <unordered_map>

//Heavily Inspired by Dean Lawson

class MemoryTracker
{
public:
	static MemoryTracker* getInstance();
	static void cleanupInstance();

	void addAllocation(void* ptr, size_t size);
	void removeAllocation(void* ptr);

	void reportAllocations(std::ostream& out);

private:
	struct AllocationRecord
	{
		AllocationRecord(int inNum, size_t inSize) : num(inNum), size(inSize) {};
		int num;
		size_t size;
	};

	MemoryTracker();
	~MemoryTracker();

	//Removes ability to copy
	MemoryTracker(const MemoryTracker&);
	MemoryTracker& operator=(const MemoryTracker&);

	std::unordered_map<void*, AllocationRecord> mAllocations;
	
	static int msAllocationNum;
	static MemoryTracker* mspInstance;
};
