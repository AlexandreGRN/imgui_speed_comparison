#include "../libraries.hpp"

namespace Thread
{
    class SingleThread
    {
    public:
        SingleThread() = default;
        ~SingleThread() = default;

        template<typename ExecutableClass>
        void run(void(ExecutableClass::*func)(), ExecutableClass* exec)
        {
            for (int i = 0; i < iterations; i++)
                (exec->*func)();
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