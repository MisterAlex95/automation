#include "math.h"
#include <rand.h>

UBYTE random_between(UBYTE min, UBYTE max)
{
    if (min >= max)
        return min;

    return (rand() % (max - min + 1)) + min;
}