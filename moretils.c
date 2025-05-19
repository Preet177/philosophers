#include "philo.h"

void ft_messages(t_philo *philosopher, int state)
{
    unsigned long timestamp;
    
    timestamp = get_current_timestamp(philosopher->shared_data);
    if (state == FORK_TAKEN)
    {
        printf("%lu %d has taken a fork\n", timestamp, philosopher->id);
    }
    else if (state == EATING)
    {
        printf("%lu %d is eating\n", timestamp, philosopher->id);
    }
    else if (state == SLEEPING)
    {
        printf("%lu %d is sleeping\n", timestamp, philosopher->id);
    }
    else if (state == THINKING)
    {
        printf("%lu %d is thinking\n", timestamp, philosopher->id);
    }
    else if (state == DIED)
    {
        printf("%lu %d died\n", timestamp, philosopher->id);
    }
}
