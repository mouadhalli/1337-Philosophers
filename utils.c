#include "philosophers.h"

long long get_timenow()
{
    struct timeval timeValue;
    gettimeofday(&timeValue, NULL);
    return ((timeValue.tv_sec * 1000) + (timeValue.tv_usec / 1000));
}

void	ft_usleep(long long sleep_duration)
{
	long long	start;

	start = get_timenow();
	usleep((sleep_duration - 5) * 1000);
	while ((get_timenow() - sleep_duration) < start)
		;
}

int exit_error(char *msg, int status)
{
	printf("Error:\n    %s\n", msg);
	return (status);
}
