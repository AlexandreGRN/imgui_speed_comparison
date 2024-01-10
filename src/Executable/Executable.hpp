#include "../libraries.hpp"

namespace Executables
{
    class Executable
    {
    public:
        Executable(int iter) : iterations(iter) {};
        ~Executable() = default;

        // very basic function to test the performance of the threads
        // it will create than sort a vector of int
        void action()
        {
            std::vector<int> v;
            for (int i = 0; i < iterations; i++)
            {
                v.push_back(i);
                std::sort(v.begin(), v.end());
            }
        }

        void setIteration(int iter) { iterations = iter; }
    private:
        int iterations = 10;
    };
}
