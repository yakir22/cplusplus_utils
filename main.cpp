#include "RunOnUiThread.h"
#include "AutoCastTest.h"
#include "CallFunctionWithNParams.h"
#include "AutoSerialize.h"
#include "EventBus.h"
#include <iostream>


std::mutex tasks_mutex;
std::deque<UiTask> tasks;

//EventBus<TestEvent>::mEvents.push_back(new TestEvent{ "test" });
void RunAnother();
void main()
{
	EventBus<TestEvent>::RegisterReceiver([](auto event) -> void {
		std::cout << "got event :: " << event->type << std::endl;
	});
	EventBus<TestEvent2>::RegisterReceiver([](auto event) -> void {
		std::cout << "got event type 2 :: " << event->type << std::endl;
	});
	RunAnother();
	TestAutoSerialize();
	TestCallFunction();
	AutoCastTest();
	RunOnUiThreadTest();
}