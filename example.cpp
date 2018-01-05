#include <iostream>
#define PICOLOG_IMPL
#include "picolog.hpp"

int main()
{
        pico::log().setMinSeverity(pico::Log::Verbose);

        pico::log().d() << "Test" << std::endl;
        pico::log().e() << "ERROR" << std::endl;
        pico::log().w() << "Count should not be " << 4 << std::endl;
        pico::log().d() << "TEST" << std::endl;
        pico::log().d() << "Some debug log" << std::endl;

        return 0;
}
