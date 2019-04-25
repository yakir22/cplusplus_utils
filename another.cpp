#include "EventBus.h"



void RunAnother()
{
	EventBus<TestEvent>::SendEvent(std::make_shared<TestEvent>("testEventType::Send"));
	EventBus<TestEvent2>::SendEvent(std::make_shared<TestEvent2>("testEventType::Send"));
	std::thread t([&]()
	{
		EventBus<TestEvent>::PostEvent(std::make_shared<TestEvent>("testEventType::Post"));
		EventBus<TestEvent2>::PostEvent(std::make_shared<TestEvent2>("testEventType::Post"));

	});
	t.join();
}