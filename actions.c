#include "philo.h"

unsigned long get_time(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
    {
        // Handle error appropriately, perhaps print an error message or exit
        // For simplicity, returning 0 here, but you should handle this case as needed
        return 0;
    }
    return ((unsigned long)tv.tv_sec * 1000) + ((unsigned long)tv.tv_usec / 1000);
}

int ft_usleep(unsigned long time)
{
    unsigned long start;

    start = get_time();
    while ((get_time() - start) < time / 1000) // Adjust time from microseconds to milliseconds for comparison
    {
        usleep(time / 100); // Sleep a fraction of the desired time to check condition more frequently
    }
    return 0;
}

unsigned long get_current_timestamp(t_data *data)
{
    unsigned long current_time;

    current_time = get_time();
    // Subtract the start time if data is provided
    return data ? current_time - data->start_time : current_time;
}

int custom_delay() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // Use microseconds part of the current time and mod by 20 to get a value in the range 0-19
    return (tv.tv_usec % 15);
}

void even_forks(t_philo *philosopher)
{
    int left_fork_index;
    int right_fork_index;

    left_fork_index = philosopher->left_fork_id - 1;
    right_fork_index = philosopher->right_fork_id - 1;

    pthread_mutex_lock(&philosopher->shared_data->forks[right_fork_index].mutex);
    if (!philosopher->shared_data->simulation_running)
    {
        pthread_mutex_unlock(&philosopher->shared_data->forks[right_fork_index].mutex);
        return;
    }
    ft_messages(philosopher, FORK_TAKEN);

    pthread_mutex_lock(&philosopher->shared_data->forks[left_fork_index].mutex);
    if (!philosopher->shared_data->simulation_running)
    {
        pthread_mutex_unlock(&philosopher->shared_data->forks[left_fork_index].mutex);
        pthread_mutex_unlock(&philosopher->shared_data->forks[right_fork_index].mutex);
        return;
    }
    ft_messages(philosopher, FORK_TAKEN);
}

void odd_forks(t_philo *philosopher)
{
    int left_fork_index = philosopher->left_fork_id - 1;
    int right_fork_index = philosopher->right_fork_id - 1;

    pthread_mutex_lock(&philosopher->shared_data->forks[left_fork_index].mutex);
    if (!philosopher->shared_data->simulation_running)
    {
        pthread_mutex_unlock(&philosopher->shared_data->forks[left_fork_index].mutex);
        return;
    }
    ft_messages(philosopher, FORK_TAKEN);

    pthread_mutex_lock(&philosopher->shared_data->forks[right_fork_index].mutex);
    if (!philosopher->shared_data->simulation_running)
    {
        pthread_mutex_unlock(&philosopher->shared_data->forks[right_fork_index].mutex);
        pthread_mutex_unlock(&philosopher->shared_data->forks[left_fork_index].mutex);
        return;
    }
    ft_messages(philosopher, FORK_TAKEN);
}
void philosopher_take_forks(t_philo *philosopher)
{
    if (!philosopher->shared_data->simulation_running) 
    return;

    if (philosopher->id % 2 == 0)
    {
        even_forks(philosopher); // Call to helper function for even ID philosophers
    } 
    else 
    {
        odd_forks(philosopher); // Call to newly created helper function for odd ID philosophers
    }
}

void philosopher_eat(t_philo *philosopher)
{
    unsigned long start_eat;

    if (!philosopher->shared_data->simulation_running) 
    return;

    start_eat = get_current_timestamp(philosopher->shared_data);
    philosopher->last_meal = start_eat;
    ft_messages(philosopher, EATING);
    
    ft_usleep(philosopher->time_to_eat * 1000UL); // Use the custom usleep function with unsigned long

    philosopher->meals_eaten++;
    
    pthread_mutex_unlock(&philosopher->shared_data->forks[philosopher->left_fork_id - 1].mutex);
    pthread_mutex_unlock(&philosopher->shared_data->forks[philosopher->right_fork_id - 1].mutex);
}

void philosopher_sleep(t_philo *philosopher)
{
    if (!philosopher->shared_data->simulation_running) 
    return;

    ft_messages(philosopher, SLEEPING);
    ft_usleep(philosopher->time_to_sleep * 1000UL); // Use the custom usleep function with unsigned long
}

void philosopher_think(t_philo *philosopher)
{
    if (!philosopher->shared_data->simulation_running) return;

    ft_messages(philosopher, THINKING);
    // Thinking does not require sleeping, but you could simulate delay here if desired
}

bool philosopher_is_dead(t_philo *philosopher)
{
    unsigned long current_time;

    current_time = get_current_timestamp(philosopher->shared_data);
    return current_time - philosopher->last_meal > philosopher->time_to_die;
}

void *philosopher_routine(void *arg)
{
    t_philo *philosopher;
    int delay_ms;

    philosopher = (t_philo *)arg;

    while (philosopher->shared_data->simulation_running && !philosopher_is_dead(philosopher))
    {
        delay_ms = custom_delay();
        ft_usleep(delay_ms * 1000); 

        philosopher_take_forks(philosopher);
        philosopher_eat(philosopher);
        philosopher_sleep(philosopher);
        philosopher_think(philosopher);
    }
    return NULL;
}

void *philosopher_routine(void *arg)
{
    t_philo *philosopher;
    int delay_ms;

    philosopher = (t_philo *)arg;

    while (1)
    {
        if (!philosopher->shared_data->simulation_running || philosopher_is_dead(philosopher))
        {
            break;
        }

        delay_ms = custom_delay();
        ft_usleep(delay_ms * 1000); 

        philosopher_take_forks(philosopher);
        philosopher_eat(philosopher);
        philosopher_sleep(philosopher);
        philosopher_think(philosopher);
    }
    return NULL;
}

