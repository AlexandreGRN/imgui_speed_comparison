#pragma once
#include "libraries.h"

class Executable
{
public:
    Executable() = default;
    ~Executable() = default;
    void long_function();
    void long_function_repeat_singleThread();
    void long_function_repeat_multiThread();
	void long_function_repeat_coroutine();

    int iterations = 1;
};
