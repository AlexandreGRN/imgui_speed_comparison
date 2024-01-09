#include "../libraries.hpp"

namespace Executable
{
    class Executable
    {
    public:
        Executable(int iter) : iterations(iter) {};
        ~Executable() = default;

        void action()
        {
            std::vector<int> v;
            for (int i = 0; i < iterations; i++)
            {
                v.push_back(i);
                std::sort(v.begin(), v.end());
            }
        }

        int iterations = 10;
    };
}
