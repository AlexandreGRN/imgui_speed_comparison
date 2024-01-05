#pragma once
#include "libraries.h"

class Chrono 
{
public:
    Chrono() = default;
    ~Chrono() = default;
    inline void start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
    inline std::chrono::milliseconds stop()
    {
        m_end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start);
    }
    inline void print_duration(std::string message = "")
    {
        std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() << " milliseconds\n";
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};
