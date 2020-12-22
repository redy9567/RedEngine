#include "MemoryTracker.h"

using namespace std;

int MemoryTracker::msAllocationNum = 0;
MemoryTracker* MemoryTracker::mspInstance = nullptr;

void MemoryTracker::addAllocation(void* ptr, size_t size)
{
	if (mAllocations.find(ptr) != mAllocations.end())
	{
		//Already exists, no need to add to the map
	}
	else
	{
		AllocationRecord rec = AllocationRecord(msAllocationNum, size);
		mAllocations.insert(pair<void*, AllocationRecord>(ptr, rec)); //Add the record
		msAllocationNum++;
	}
}

void MemoryTracker::removeAllocation(void* ptr)
{
	unordered_map<void*, AllocationRecord>::iterator it = mAllocations.find(ptr);

	if (it == mAllocations.end())
	{
		//Doesn't exist.... Do nothing
	}
	else
	{
		mAllocations.erase(it);
	}
}

MemoryTracker* MemoryTracker::getInstance()
{
	if (mspInstance == nullptr)
	{
		mspInstance = new MemoryTracker();
	}

	return mspInstance;
}

void MemoryTracker::cleanupInstance()
{
	delete mspInstance;
}

void MemoryTracker::reportAllocations(ostream& out)
{
	out << "Current Memory Allocations:\n";

	unordered_map<void*, AllocationRecord>::iterator it;
	for (it = mAllocations.begin(); it != mAllocations.end(); it++)
	{
		out << "Address: " << it->first << " Size: " << it->second.size << " Allocation_Num: " << it->second.num << endl;
	}
}

MemoryTracker::MemoryTracker()
{

}

MemoryTracker::~MemoryTracker()
{
	cout << "Memory Tracker is being deleted\n";
	reportAllocations(cout);
}