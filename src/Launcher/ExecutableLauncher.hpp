#include "../libraries.hpp"

namespace Launchers
{
    class ExecutableLauncher
    {
    public:
        // Run the `function` passed in argument in a specific `ThreadType` and return the time it took to execute it
        template<typename ThreadType, typename ExecutableClass, typename Chrono>
        int runFunction(void(ExecutableClass::*func)(), ExecutableClass* exec, Chrono& chrono)
        {
            ThreadType thread;
            chrono.start();
            thread.run(func, exec);
            return chrono.stop().count();
        }
    };
}