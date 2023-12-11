//Inspired by Dean Lawson, Champlain College

#pragma once
#include <unordered_map>
#include <ostream>

class MemoryTracker
{
public:
	static MemoryTracker* getInstance();
	static void cleanupInstance();

	void addAllocation(void* ptr, size_t size);
	void addIsolatedAllocation(void* ptr, size_t size);
	void removeAllocation(void* ptr);
	void removeIsolatedAllocation(void* ptr);

	void reportAllocations(std::ostream& stream);

private:
	struct AllocationRecord
	{
		AllocationRecord(int n, size_t s) : num(n), size(s) {};
		int num;
		size_t size;
	};

	MemoryTracker() {};
	~MemoryTracker() {};

	std::unordered_map<void*, AllocationRecord> mAllocations;
	std::unordered_map<void*, AllocationRecord> mIsolatedAllocations;

	static int msAllocationNum;
	static int msIsolatedAllocationNum;

	static MemoryTracker* mspInstance;
};
