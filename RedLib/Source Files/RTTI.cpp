#include "RTTI.h"
#include <assert.h>
#include <string>
#include <typeinfo>

using namespace std;

RTTISystem* RTTISystem::mspInstance = nullptr;

RTTINameFieldInfo::RTTINameFieldInfo(string rttiTypeName)
	: RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<string>(), "RTTITypeName"),
	mRTTITypeName(rttiTypeName)
{

}

RTTIType::~RTTIType()
{

}

RTTIType::RTTIType(string typeName, size_t typeInfoHash, bool isPrimitiveType)
{
	mTypeName = typeName;
	mTypeInfoHash = typeInfoHash;
	mIsPrimitiveType = isPrimitiveType;
}

RTTIType* RTTIObject::getType()
{
	return RTTISystem::getInstance()->getRTTITypeFor(this);
}

RTTIObject::RTTIObject()
{
	getType(); //Calling the getType function, will register this RTTIClass when it doesn't exist
}

RTTISystem* RTTISystem::getInstance()
{
	if (!mspInstance)
		mspInstance = new RTTISystem();

	return mspInstance;
}

void RTTISystem::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance;
	}
}

RTTIType* RTTISystem::getRTTITypeFor(RTTIObject* obj)
{
	//Look up if the RTTI type is registered
	for (std::vector<RTTIType*>::iterator i = mRegisteredTypes.begin(); i != mRegisteredTypes.end(); ++i)
	{
		if ((*i)->mTypeInfoHash == typeid(*obj).hash_code())
			return *i;
	}

	//If it doesn't exist register it

}

template<typename T>
RTTIType* RTTISystem::getRTTIType()
{
	//Look up if the RTTI type is registered
	for (std::vector<RTTIType*>::iterator i = mRegisteredTypes.begin(); i != mRegisteredTypes.end(); ++i)
	{
		if ((*i)->mTypeInfoHash == typeid(T).hash_code())
			return *i;
	}

	//If it doesn't exist, throw an assert. (Maybe we want this to lazy register later?)
	assert(false);
}

RTTISystem::RTTISystem()
{
	RTTIType* boolRTTI = createRTTIType<bool>("bool", true);
	RTTIType* intRTTI = createRTTIType<int>("int", true);
	RTTIType* floatRTTI = createRTTIType<float>("float", true);
	RTTIType* stringRTTI = createRTTIType<string>("string", true);

	mRegisteredTypes.push_back(boolRTTI);
	mRegisteredTypes.push_back(intRTTI);
	mRegisteredTypes.push_back(floatRTTI);
	mRegisteredTypes.push_back(stringRTTI);
}

template<typename T>
RTTIType* RTTISystem::createRTTIType(std::string typeName, bool isPrimitiveType)
{
	return new RTTIType(typeName, typeid(T).hash_code(), isPrimitiveType);
}
