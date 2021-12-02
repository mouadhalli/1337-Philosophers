#include "philosophers.h"

long long get_timeNow()
{
    struct timeval timeValue;
    gettimeofday(&timeValue, NULL);
    return ((timeValue.tv_sec * 1000) + (timeValue.tv_usec / 1000));
}