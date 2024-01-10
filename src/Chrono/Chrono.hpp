#include "../libraries.hpp"
namespace Chronos
{
    class Chrono 
    {
    public:
        Chrono() = default;
        ~Chrono() = default;

        // Start the chrono
        inline void start()
        {
            m_start = std::chrono::high_resolution_clock::now();
        }

        // Stop the chrono and return the duration
        inline std::chrono::milliseconds stop()
        {
            m_end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start);
        }

        // Print the duration
        inline void print_duration(std::string message = "")
        {
            std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() << " milliseconds\n";
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
    };
}