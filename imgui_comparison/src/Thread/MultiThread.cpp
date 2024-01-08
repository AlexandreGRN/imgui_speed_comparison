#include "../libraries.h"
#include <thread>

namespace Thread{
    class MultiThread
    {
    public:
        MultiThread() = default;
        ~MultiThread() = default;

        template <typename ExecutableClass>
        void run(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            std::vector<std::jthread> threads;

            for (int i = 0; i < iterations; i++)
                threads.push_back(std::jthread(&MultiThread::doRun<ExecutableClass>, this, func, exec));
        }

        void set_iterations(int iterations)
        {
            if (iterations <= 10)
                this->iterations = iterations;
        }

    private:
        int iterations = 10;

        template <typename ExecutableClass>
        void doRun(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            (exec->*func)();
        }
    };
}