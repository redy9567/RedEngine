#pragma once
#include <vector>
#include <string>

class RTTIType; //Forward declare, since complex RTTI types will have FieldInfos, that point to other RTTI types that they contain (creating a circular declaration loop)


// Info related characteristics for a given field in a compound RTTI object
class RTTIFieldInfo
{
	friend class RTTIObject;

public:
	RTTIFieldInfo(RTTIType* type, std::string fieldName, char valueOffset) : mType(type), mFieldName(fieldName), mValueOffset(mValueOffset) {}
	virtual ~RTTIFieldInfo() {}; //Doesn't hold ownership of the RTTITypes

	RTTIType* getFieldType() { return mType; }
	std::string getFieldName() { return mFieldName; }

private:
	RTTIFieldInfo() = delete;

	RTTIType* mType;
	std::string mFieldName;
	char mValueOffset;
};


// FieldInfo that represents the name for an RTTIType. This must be unique and everyone RTTIType is required to have one of these.
class RTTINameFieldInfo : public RTTIFieldInfo
{
	friend class RTTIObject;

public:
	RTTINameFieldInfo(std::string rttiTypeName);
	~RTTINameFieldInfo() {};

	std::string getRTTITypeName() { return mRTTITypeName; }

private:
	RTTINameFieldInfo() = delete;

	std::string mRTTITypeName;
};


// Two types, primative ones, and complex ones defined by a set of fields
class RTTIType
{
public:
	std::string getName() { return mTypeName; }

private:
	friend class RTTISystem;

	RTTIType() = delete;
	~RTTIType() {};

	RTTIType(std::string typeName, std::size_t typeInfoHash, bool isPrimitiveType = false);

	std::string mTypeName;
	std::size_t mTypeInfoHash;
	bool mIsPrimitiveType;
	std::vector<RTTIFieldInfo> mRTTIFieldInfos;
};



class RTTIField
{
private:
	RTTIField() = delete;
	~RTTIField() {};

	RTTIField(RTTIFieldInfo* info, void* value) : mInfo(info), mValue(value) {};

	RTTIFieldInfo* mInfo;
	void* mValue;
};



class RTTIObject
{
	friend class RTTISystem;

public:
	virtual ~RTTIObject();

	RTTIType* getType();

protected:
	RTTIObject();

private:
	virtual std::vector<RTTIFieldInfo> defineRTTIObject() = 0;

	std::string mObjectName;
	std::vector<RTTIField*> mFields;
};



class RTTISystem
{
public:
	static RTTISystem* getInstance();
	void cleanupInstance();

	RTTIType* getRTTITypeFor(RTTIObject* obj);

	template<typename T>
	RTTIType* getRTTIType();

	void registerRTTIObjectClass(RTTIObject* obj);

	void notifyRTTIObjectDestruct(RTTIObject* obj);

	void update();

private:
	RTTISystem();
	~RTTISystem() {};

	bool isRTTITypeRegisteredForObject(RTTIObject* obj);
	void internalRegisterRTTIObjectClass(RTTIObject* obj);

	template<typename T>
	RTTIType* createRTTIType(std::string typeName, bool isPrimitiveType = false);

	template<typename T>
	RTTIType* createRTTIType(T& typeExample, std::string typeName);

	static RTTISystem* mspInstance;

	std::vector<RTTIObject*> mObjectsWithUnregisteredTypes;
	std::vector<RTTIType*> mRegisteredTypes;

};



class TestObject : public RTTIObject
{
public:
	TestObject(bool b, int i, float f, std::string s) : mBool(b), mInt(i), mFloat(f), mString(s) {}
	~TestObject() {}

private:
	std::vector<RTTIFieldInfo> defineRTTIObject();

	bool mBool;
	int mInt;
	float mFloat;
	std::string mString;
};