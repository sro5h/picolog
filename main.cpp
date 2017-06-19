#include "Log.hpp"

int main()
{
        LOG.setMinSeverity(Log::WARNING);

        LOG << Log::DEBUG << "Test";
        LOG.e() << "ERROR";
        Log::logger.w() << "Count should not be " << 4;

        return 0;
}
