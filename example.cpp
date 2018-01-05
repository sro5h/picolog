#include <iostream>
#define PICOLOG_IMPL
#include "picolog.hpp"

struct vec2
{
        float x;
        float y;
};

pico::Log& operator<<(pico::Log& log, const vec2& v)
{
        return log << "[" << v.x << "," << v.y << "]";
}

int main()
{
        pico::log().setMinSeverity(pico::Log::Verbose);

        pico::log().d() << "Test" << std::endl;
        pico::log().e() << "ERROR" << std::endl;
        pico::log().w() << "Count should not be " << 4 << std::endl;
        pico::log().d() << "TEST" << std::endl;
        pico::log().d() << "Some debug log" << std::endl;

        vec2 v = { 3.5, 2.3 };
        pico::log().d() << v << std::endl;

        return 0;
}
