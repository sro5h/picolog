#include "Log.hpp"

int main()
{
        Log::e() << "test";
        Log::d() << "test";
        Log::v() << "test" << 20;

        return 0;
}
