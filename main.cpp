#include "Log.hpp"

int main()
{
        LOG << Log::DEBUG << "Test";
        LOG.e() << "ERROR";

        return 0;
}
