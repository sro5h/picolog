#include "Log.hpp"

int main()
{
        LOG_ERR << "test";
        LOG_DEB << "test";
        LOG_VER << "test" << 20;
        return 0;
}
