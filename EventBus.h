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
		GetReceivers().push_back(receiver);
	}

	template<class... _Types>
	static void Send(_Types&&... params)
	{
		SendEvent(std::make_shared<T>(std::forward<_Types>(params)...));
	}

	static void SendEvent(std::shared_ptr<T> event)
	{
		for ( auto &receiver : GetReceivers())
		{
			receiver(event);
		}	
	}

	template<class... _Types>
	static void Post(_Types&&... params)
	{
		PostEvent(std::make_shared<T>(std::forward<_Types>(params)...));
	}

	static void PostEvent(std::shared_ptr<T> event)
	{
		RunOnUiThreadNoWait(UiTask([event]() -> boost::any{
			SendEvent(event);
			return true;
		}));
	}

private:
	//inline static std::vector<std::function<void(std::shared_ptr<T>)>>	mReceivers; // crashing clang++ on ndk17c
	static std::vector<std::function<void(std::shared_ptr<T>)>> &GetReceivers()
	{
		static std::vector<std::function<void(std::shared_ptr<T>)>>	mReceivers;
		return mReceivers;
	}

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

struct GenericEvent
{
	constexpr GenericEvent(int code) noexcept : code(code) {}
	int code;
};

/*
	All events will be handled in the main thread regardless if they are sync(Send) or async(Post)
	usage::
	struct TestEvent : GenericEvent{}; -- inheritance from GenericEvent is optional but each event type should have a class/struct of its own
	EventBus<TestEvent>::RegisterReceiver([](auto event) -> void {
	});
	using TestEventBus = EventBus<TestEvent>;

	// send sync event
	TestEventBus::SendEvent(std::make_shared<TestEvent>("testEventType::Send")); // explicist event constraction
	TestEventBus::Send("testEventType::Send"); // implicit event constraction

	// post async event
	TestEventBus::PostEvent(std::make_shared<TestEvent>("testEventType::Send")); // explicist event constraction
	TestEventBus::Post("testEventType::Send"); // implicit event constraction
*/
