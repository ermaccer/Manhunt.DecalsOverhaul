#include "core.h"
#include "Maths.h"

int CMaths::GetRandomInt(int min, int max)
{
    return CallAndReturn<int, 0x493B90, int, int>(min, max);
}
