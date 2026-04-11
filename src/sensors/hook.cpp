#include "hook.h"
#include <vector>

//

namespace ssr
{
    std::vector<void (*)(JsonArray)> hooks;

    //

    void onRead(void (*hook)(JsonArray))
    {
        hooks.push_back(hook);
    }
}

namespace ssr::internal
{
    void invokeOnReadHooks(JsonArray &arr)
    {
        for (void (*hook)(JsonArray) : hooks)
        {
            hook(arr);
        }
    }
}