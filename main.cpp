#define PICOLOG_IMPL
#include "picolog.hpp"
#include <iostream>

int main()
{
        log().setMinSeverity(Log::Verbose);

        log().d() << "Test" << std::endl;
        log().e() << "ERROR" << std::endl;
        log().w() << "Count should not be " << 4 << std::endl;
        log().d() << "TEST" << std::endl;
        log().d() << "Some debug log" << std::endl;

        return 0;
}
