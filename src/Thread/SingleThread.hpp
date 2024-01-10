#include "../libraries.hpp"

namespace Threads
{
    class SingleThread
    {
    public:
        SingleThread() = default;
        ~SingleThread() = default;

        // Run the `function` passed in argument x times
        template<typename ExecutableClass>
        void run(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            for (int i = 0; i < iterations; i++)
                (exec->*func)();
        }

        // Set the number of iterations
        void set_iterations(int iterations)
        {
            if (iterations <= 10)
                this->iterations = iterations;
        }

    private:
        int iterations = 10;
    };
}