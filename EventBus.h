#pragma once
#include <list>
#include <vector>
#include <string>
#include <functional>
#include "RunOnUiThread.h"

template<typename T>
class EventBus
{
public:
	static void RegisterReceiver(std::function<void(std::shared_ptr<T>)> receiver)
	{
		mReceivers.push_back(receiver);
	}
	static void SendEvent(std::shared_ptr<T> event)
	{
		for ( auto &receiver : mReceivers) 
		{
			receiver(event);
		}	
	}
	static void PostEvent(std::shared_ptr<T> event)
	{
		RunOnUiThreadNoWait(UiTask([event]() -> boost::any{
			SendEvent(event);
			return true;
		}));
	}

private:
	inline static std::vector<std::function<void(std::shared_ptr<T>)>>	mReceivers;
};


struct TestEvent
{
	TestEvent(const std::string &type):
		type(type){}
	std::string type;
}; 

struct TestEvent2 : TestEvent {
	TestEvent2(const std::string &type) : TestEvent(type){}
};

/*
struct TestEvent2
{
	TestEvent2(const std::string &type) :
		type(type) {}
	std::string type;
};
*/
