#include "ObjectSerializer.h"
#include <assert.h>
#include <string>

using namespace std;

RTTISystem* RTTISystem::mspInstance = nullptr;
ObjectSerializer* ObjectSerializer::mspInstance = nullptr;

const int INDENT_DELTA = 4;

RTTIType::~RTTIType()
{

}

RTTIType::RTTIType(string typeName, size_t typeInfoHash, bool isPrimitiveType)
{
	mTypeName = typeName;
	mTypeInfoHash = typeInfoHash;
	mIsPrimitiveType = isPrimitiveType;
}

RTTIField::~RTTIField()
{

}

RTTIField::RTTIField(RTTIType* type, std::string fieldName, void* value)
{
	mType = type;
	mFieldName = fieldName;
	mValue = value;
}

RTTIObject::~RTTIObject()
{
	
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

RTTISystem::~RTTISystem()
{

}

template<typename T>
RTTIType* RTTISystem::createRTTIType(std::string typeName, bool isPrimitiveType)
{
	return new RTTIType(typeName, typeid(T).name(), isPrimitiveType);
}

ObjectSerializer* ObjectSerializer::getInstance()
{
	if (!mspInstance)
		mspInstance = new ObjectSerializer();

	return mspInstance;
}

void ObjectSerializer::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

ObjectSerializer::ObjectSerializer()
{

}

ObjectSerializer::~ObjectSerializer()
{

}

void ObjectSerializer::indent()
{
	for (int i = mIndent; i < mIndent; ++i)
	{
		mOutputFileStream << " ";
	}
}

void ObjectSerializer::beginObject(string filepath)
{
	assert(!mOutputFileStream.is_open());

	mOutputFileStream.open(filepath);

	indent();

	mOutputFileStream << '{' << endl;

	mIndent += INDENT_DELTA;
}

void ObjectSerializer::endObject()
{
	assert(mOutputFileStream.is_open());

	mIndent -= INDENT_DELTA;

	indent();

	mOutputFileStream << '}' << endl;

	if (mIndent == 0)
	{
		mOutputFileStream.close();
	}
}

void ObjectSerializer::writeBool(string fieldName, bool value)
{
	assert(mOutputFileStream.is_open());

	indent();

	string stringValue = value ? "true" : "false";

	mOutputFileStream << "\"" << fieldName << "\": " << stringValue << endl;
}

void ObjectSerializer::writeInt(string fieldName, int value)
{
	assert(mOutputFileStream.is_open());

	indent();

	string stringValue = to_string(value);

	mOutputFileStream << "\"" << fieldName << "\": " << stringValue << endl;
}

void ObjectSerializer::writeFloat(string fieldName, float value)
{
	assert(mOutputFileStream.is_open());

	indent();

	string stringValue = to_string(value);

	mOutputFileStream << "\"" << fieldName << "\": " << stringValue << endl;
}

void ObjectSerializer::writeString(string fieldName, string value)
{
	assert(mOutputFileStream.is_open());

	indent();

	mOutputFileStream << "\"" << fieldName << "\": \"" << value << "\"" << endl;
}
