#define PICOLOG_IMPL
#include "picolog.hpp"
#include <iostream>

Log log(std::cout);

int main()
{
        log.setMinSeverity(Log::VERBOSE);

        log << Log::DEBUG << "Test" << std::endl;
        log.e() << "ERROR" << std::endl;
        log.w() << "Count should not be " << 4 << std::endl;
        log.d() << "TEST" << std::endl;

        return 0;
}
