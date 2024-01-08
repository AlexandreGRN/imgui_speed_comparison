#include "../libraries.h"

namespace Thread{
    class CoroutineThread
    {
    public:
        CoroutineThread() = default;
        ~CoroutineThread() = default;

        template <typename ExecutableClass>
        void run(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            for (int i = 0; i < iterations; i++)
            {
                boost::coroutines2::coroutine<void>::pull_type coro([&](boost::coroutines2::coroutine<void>::push_type& yield)
                {
                    (exec->*func)();
                    yield();
                });
                while (coro) {
                    coro();
                }
            }
        }

        void set_iterations(int iterations)
        {
            if (iterations <= 10)
                this->iterations = iterations;
        }

    private:
        int iterations = 10;
    };
}