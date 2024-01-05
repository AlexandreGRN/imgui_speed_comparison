#include "Executable.h"

void Executable::long_function()
{
    std::vector<int> v;
    for (int i = 0; i < iterations; i++)
    {
        v.push_back(i);
        std::sort(v.begin(), v.end());
    }
}

void Executable::long_function_repeat_singleThread()
{
    for (int i = 0; i < 10; i++)
        long_function();
}

void Executable::long_function_repeat_multiThread()
{
    std::vector<std::jthread> threads;

    for (int i = 0; i < 10; i++)
        threads.push_back(std::jthread(&Executable::long_function, this));
}

void Executable::long_function_repeat_coroutine()
{
	boost::coroutines2::coroutine<void>::pull_type coro([&](boost::coroutines2::coroutine<void>::push_type& yield)
	{
    	for (int i = 0; i < 10; ++i) {
			long_function();
			yield();
		}
	});

	while (coro) {
		coro();
	}
}