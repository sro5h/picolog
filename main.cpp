#define PICOLOG_IMPL
#include "picolog.hpp"
#include <iostream>

Log log(std::cout);

int main()
{
        log.setMinSeverity(Log::Verbose);

        log(Log::Debug) << "Test" << std::endl;
        log(Log::Error) << "ERROR" << std::endl;
        log(Log::Warning) << "Count should not be " << 4 << std::endl;
        log(Log::Verbose) << "TEST" << std::endl;

        return 0;
}
