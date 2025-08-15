#pragma once
#include <fstream>

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