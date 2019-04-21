#include <windows.h>
#include <iostream>
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <boost/any.hpp>

typedef std::packaged_task<boost::any()> UiTask;

std::mutex tasks_mutex;
std::deque<UiTask> tasks;

boost::any proxy(const std::string &p)
{
	return boost::any(p + "b");
}

// TODO :: this will stack if called from the ui thread
auto RunOnUiThread(UiTask &task)
{
	std::future<boost::any> result = task.get_future();
	{
		std::lock_guard<std::mutex> lock(tasks_mutex);
		tasks.push_back(std::move(task));
	}
	return result.get();

}

bool RunOnUiThreadTest()
{
	boost::any output;
	std::thread t([&]()
	{
		std::string url = "a";
		output = RunOnUiThread(UiTask([&]() -> boost::any
		{
			return proxy(url);
		}));
		Sleep(300);
		RunOnUiThread(UiTask([&]() -> boost::any
		{
			std::cout << "output = " << boost::any_cast<std::string>(output) << std::endl;
			return 0;
		}));
	});

	Sleep(300);
	int total = 2;
	while (total)
	{
		std::unique_lock<std::mutex> lock(tasks_mutex);
		while (!tasks.empty())
		{
			auto task(std::move(tasks.front()));
			tasks.pop_front();
			lock.unlock();
			task();
			lock.lock();
			total--;
		}
	}
	t.join();
	return boost::any_cast<std::string>(output) == "ab";
}

