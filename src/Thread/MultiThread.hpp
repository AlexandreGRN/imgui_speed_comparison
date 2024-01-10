#include "../libraries.hpp"

namespace Threads{
    class MultiThread
    {
    public:
        MultiThread() = default;
        ~MultiThread() = default;

        // Run the `function` passed in argument x times
        template <typename ExecutableClass>
        void run(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            std::vector<std::jthread> threads;

            for (int i = 0; i < iterations; i++)
                threads.push_back(std::jthread(&MultiThread::doRun<ExecutableClass>, this, func, exec));
        }

        // Set the number of iterations
        void set_iterations(int iterations)
        {
            if (iterations <= 10)
                this->iterations = iterations;
        }

    private:
        int iterations = 10;

        // Run the `function` passed in argument | This function is used and needed for threads
        template <typename ExecutableClass>
        void doRun(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            (exec->*func)();
        }
    };
}