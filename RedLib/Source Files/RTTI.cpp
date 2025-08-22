#include "RTTI.h"
#include <assert.h>
#include <string>
#include <typeinfo>

using namespace std;

RTTISystem* RTTISystem::mspInstance = nullptr;

const string RTTI_NAME_FIELD_INFO = "RTTITypeName";

RTTINameFieldInfo::RTTINameFieldInfo(string rttiTypeName)
	: RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<string>(), RTTI_NAME_FIELD_INFO, 0),
	mRTTITypeName(rttiTypeName)
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
	RTTISystem::getInstance()->registerRTTIObjectClass(this);
}

RTTIObject::~RTTIObject()
{
	RTTISystem::getInstance()->notifyRTTIObjectDestruct(this);
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
	update();

	//Look up if the RTTI type is registered
	for (vector<RTTIType*>::iterator i = mRegisteredTypes.begin(); i != mRegisteredTypes.end(); ++i)
	{
		if ((*i)->mTypeInfoHash == typeid(*obj).hash_code())
			return *i;
	}

	//If it doesn't exist, throw an assert.
	assert(false);
}

template<typename T>
RTTIType* RTTISystem::getRTTIType()
{
	update();

	//Look up if the RTTI type is registered
	for (vector<RTTIType*>::iterator i = mRegisteredTypes.begin(); i != mRegisteredTypes.end(); ++i)
	{
		if ((*i)->mTypeInfoHash == typeid(T).hash_code())
			return *i;
	}

	//If it doesn't exist, throw an assert.
	assert(false);
}

void RTTISystem::registerRTTIObjectClass(RTTIObject* obj)
{
	if (!isRTTITypeRegisteredForObject(obj))
		mObjectsWithUnregisteredTypes.push_back(obj);
}

void RTTISystem::notifyRTTIObjectDestruct(RTTIObject* obj)
{
	//If this class was on the list of objects to be registered, remove it to prevent dangling pointers.
	for (vector<RTTIObject*>::iterator i = mObjectsWithUnregisteredTypes.begin(); i != mObjectsWithUnregisteredTypes.end(); ++i)
	{
		if (*i == obj)
		{
			mObjectsWithUnregisteredTypes.erase(i);
			break;
		}
	}
}

void RTTISystem::update()
{
	//We are now going to register any RTTITypes that are waiting to be registered.

	for (vector<RTTIObject*>::iterator i = mObjectsWithUnregisteredTypes.begin(); i != mObjectsWithUnregisteredTypes.end(); ++i)
	{
		if (!isRTTITypeRegisteredForObject(*i))
			internalRegisterRTTIObjectClass(*i);
	}

	mObjectsWithUnregisteredTypes.clear();
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

bool RTTISystem::isRTTITypeRegisteredForObject(RTTIObject* obj)
{
	//Look up if the RTTI type is registered
	for (std::vector<RTTIType*>::iterator i = mRegisteredTypes.begin(); i != mRegisteredTypes.end(); ++i)
	{
		if ((*i)->mTypeInfoHash == typeid(*obj).hash_code())
			return true;
	}

	return false;
}

void RTTISystem::internalRegisterRTTIObjectClass(RTTIObject* obj)
{
	vector<RTTIFieldInfo> rttiInfo = obj->defineRTTIObject();

	//Search for the RTTINameField and extract the name of the RTTI that we are registering
	string rttiName = "";
	for (vector<RTTIFieldInfo>::iterator i = rttiInfo.begin(); i != rttiInfo.end(); ++i)
	{
		if ((*i).getFieldName() == RTTI_NAME_FIELD_INFO)
		{
			rttiName = ((RTTINameFieldInfo*)&(*i))->getRTTITypeName();

			rttiInfo.erase(i);
			break;
		}
	}

	//Create the new RTTIType
	RTTIType* newRTTI = createRTTIType(*obj, rttiName);
	newRTTI->mRTTIFieldInfos = rttiInfo;
	
	mRegisteredTypes.push_back(newRTTI);

}

template<typename T>
RTTIType* RTTISystem::createRTTIType(std::string typeName, bool isPrimitiveType)
{
	return new RTTIType(typeName, typeid(T).hash_code(), isPrimitiveType);
}

template<typename T>
RTTIType* RTTISystem::createRTTIType(T& typeExample, std::string typeName)
{
	return new RTTIType(typeName, typeid(T).hash_code(), false);
}

vector<RTTIFieldInfo> TestObject::defineRTTIObject()
{
	vector<RTTIFieldInfo> rttiLayout;

	rttiLayout.push_back(RTTINameFieldInfo("TestObject"));
	rttiLayout.push_back(RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<bool>(), "BoolF1", (char*)this - (char*)&mBool));
	rttiLayout.push_back(RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<int>(), "Int", (char*)this - (char*)&mInt));
	rttiLayout.push_back(RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<float>(), "Floooat", (char*)this - (char*)&mFloat));
	rttiLayout.push_back(RTTIFieldInfo(RTTISystem::getInstance()->getRTTIType<string>(), "Str", (char*)this - (char*)&mString));

	return rttiLayout;
}