#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "json.hpp"

class AutoMemberBase
{
public:
	virtual void doJsonOut(void *cls, nlohmann::json &jsonObject) = 0;
	virtual void doJsonIn(void *cls, nlohmann::json &jsonObject) = 0;
};

class AutoSerializationClass
{
protected:
	std::vector<AutoMemberBase*> mAllMembers;
public:
	void add(AutoMemberBase*p)
	{
		mAllMembers.push_back(p);
	}
	std::string serialize()
	{
		nlohmann::json jsonObject;
		for ( auto m : mAllMembers )
		{
			m->doJsonOut(this, jsonObject);
		}
		return jsonObject.dump();
	}
	void deserialize(const std::string &_json)
	{
		nlohmann::json jsonObject = nlohmann::json::parse(_json);
		for (auto m : mAllMembers)
		{
			m->doJsonIn(this, jsonObject);
		}
	}

};

template <typename T>
class AutoMember :  public AutoMemberBase
{
public:
	AutoMember(AutoSerializationClass *container,std::string &&name,size_t offset)
	{
		mName = name;
		mOffset = offset;
		container->add(this);
	}
	size_t mOffset;
	std::string mName;
	void doJsonOut(void *cls, nlohmann::json &jsonObject)
	{
		T* val = (T*)((char*)cls + mOffset);
		jsonObject[mName] = *val;
	}
	void doJsonIn(void *cls, nlohmann::json &jsonObject) 
	{
		T* val = (T*)((char*)cls + mOffset);
		*val = jsonObject[mName];
	}
};


#define dclmember(cls,type,name,def) public:type name{def}; private:AutoMember<type> __ ## name {this,#name, offsetof(cls,name) }



struct TestS : public AutoSerializationClass
{
	dclmember(TestS, int, anotherOne);
	dclmember(TestS, float, score);
	dclmember(TestS, std::string, myName);
};


void TestAutoSerialize()
{
	TestS test;
	test.score = 55.5f;
	test.myName = "lalala";
	test.anotherOne = 66;

	std::string s = test.serialize();

	std::cout << s << std::endl;

	TestS test2;
	test2.deserialize(s);

	std::cout << test.serialize() << std::endl;


	//test2.
}

