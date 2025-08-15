#include "ObjectSerializer.h"
#include <assert.h>
#include <string>

using namespace std;

ObjectSerializer* ObjectSerializer::mspInstance = nullptr;

const int INDENT_DELTA = 4;

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
