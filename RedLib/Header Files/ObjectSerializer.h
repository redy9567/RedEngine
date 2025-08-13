#pragma once
#include <fstream>
#include <vector>

class RTTIType
{
public:
	std::string getName() { return mTypeName; }

private:
	friend class RTTISystem;

	RTTIType() = delete;
	~RTTIType();

	RTTIType(std::string typeName, std::size_t typeInfoHash, bool isPrimitiveType = false);

	std::string mTypeName;
	std::size_t mTypeInfoHash;
	bool mIsPrimitiveType;
};

class RTTIField
{
private:
	RTTIField() = delete;
	~RTTIField();

	RTTIField(RTTIType* type, std::string fieldName, void* value);

	RTTIType* mType;
	std::string mFieldName;
	void* mValue;
};

class RTTIObject
{
public:
	virtual ~RTTIObject();

	RTTIType* getType();

private:
	RTTIObject();

	virtual void defineRTTIObject() = 0;

	std::string mObjectName;
	std::vector<RTTIField*> mFields;
};

class RTTISystem
{
public:
	static RTTISystem* getInstance();
	void cleanupInstance();

	template<typename T>
	void registerRTTIObjectClass(std::string );

private:
	RTTISystem();
	~RTTISystem();

	template<typename T>
	RTTIType* createRTTIType(std::string typeName, bool isPrimitiveType = false);

	static RTTISystem* mspInstance;

	std::vector<RTTIType*> mRegisteredTypes;

};

class TestObject
{
private:
	bool mBool;
	int mInt;
	float mFloat;
	std::string mString;
};

class ObjectSerializer
{
public:
	static ObjectSerializer* getInstance();
	void cleanupInstance();

private:
	ObjectSerializer();
	~ObjectSerializer();

	void indent();
	void beginObject(std::string filepath);
	void endObject();

	void writeBool(std::string fieldName, bool value);
	void writeInt(std::string fieldName, int value);
	void writeFloat(std::string fieldName, float value);
	void writeString(std::string fieldName, std::string value);

	std::ofstream mOutputFileStream;
	int mIndent = 0;

	static ObjectSerializer* mspInstance;
};