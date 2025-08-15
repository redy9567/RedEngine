#pragma once
#include <vector>
#include <string>

class RTTIType; //Forward declare, since complex RTTI types will have FieldInfos, that point to other RTTI types that they contain (creating a circular declaration loop)


// Info related characteristics for a given field in a compound RTTI object
class RTTIFieldInfo
{
	friend class RTTIObject;

protected:
	RTTIFieldInfo(RTTIType* type, std::string fieldName) : mType(type), mFieldName(fieldName) {}
	virtual ~RTTIFieldInfo() {}; //Doesn't hold ownership of the RTTITypes

private:
	RTTIFieldInfo() = delete;

	RTTIType* mType;
	std::string mFieldName;
};


// FieldInfo that represents the name for an RTTIType. This must be unique and everyone RTTIType is required to have one of these.
class RTTINameFieldInfo : RTTIFieldInfo
{
	friend class RTTIObject;

private:
	RTTINameFieldInfo(std::string rttiTypeName);

	RTTINameFieldInfo() = delete;
	~RTTINameFieldInfo() {};

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
public:
	virtual ~RTTIObject() {};

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

	RTTIType* getRTTITypeFor(RTTIObject* obj);

	template<typename T>
	RTTIType* getRTTIType();

private:
	RTTISystem();
	~RTTISystem() {};

	void registerRTTIObjectClass(std::stri);

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