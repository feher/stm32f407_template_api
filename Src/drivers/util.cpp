#include "util.hpp"

namespace Util
{
    void busyWait(int ms)
    {
        for (int i = 0; i < ms * 1000; ++i)
        {
            // Nothing.
        }
    }
} // namespace Util