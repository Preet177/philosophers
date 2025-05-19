#include "philo.h"

void initialise_forks(t_data *data) 
{
    int i;
    i = 0;

    data->forks = (t_fork *)malloc(sizeof(t_fork) * data->num_philosophers);
    if (!data->forks) 
    {
        return ; // Exit program on critical error
    }
    while (i < data->num_philosophers) 
    {
        data->forks[i].id = i + 1;
        pthread_mutex_init(&(data->forks[i].mutex), NULL);
        i++;
    }
}

void init_philosophers(t_data *data) 
{
    int i;
    i = 0;

    data->philosophers = (t_philo *)malloc(sizeof(t_philo) * data->num_philosophers);
    if (!data->philosophers) 
    {
        return ; 
    }
    while (i < data->num_philosophers) 
    {
        data->philosophers[i].id = i + 1; 
        data->philosophers[i].last_meal = 0;
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].left_fork_id = i;
        data->philosophers[i].right_fork_id = (i + 1) % data->num_philosophers;
        data->philosophers[i].shared_data = data;
        data->philosophers[i].time_to_eat = data->time_to_eat;
        data->philosophers[i].time_to_sleep = data->time_to_sleep;
        data->philosophers[i].time_to_die = data->time_to_die;
        i++;
    }
}

Reducing line code:

void init_philosophers(t_data *data) 
{
    int i = 0;
    size_t size;

    size = sizeof(t_philo) * data->num_philosophers;
    data->philosophers = malloc(size);
    if (!data->philosophers) 
    {
        return; 
    }
    while (i < data->num_philosophers) 
    {
        data->philosophers[i].id = i + 1; 
        data->philosophers[i].last_meal = 0;
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].left_fork_id = i;
        data->philosophers[i].right_fork_id = (i + 1) % data->num_philosophers;
        data->philosophers[i].shared_data = data;
        data->philosophers[i].time_to_eat = data->time_to_eat;
        data->philosophers[i].time_to_sleep = data->time_to_sleep;
        data->philosophers[i].time_to_die = data->time_to_die;
        i++;
    }
}
