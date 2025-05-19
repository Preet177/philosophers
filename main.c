#include "philo.h"

void *single_philosopher_routine(void *arg)
{
    t_philo *philosopher;

    philosopher = (t_philo *)arg;
    
    ft_messages(philosopher, FORK_TAKEN);
    ft_usleep(philosopher->time_to_die * 1000);
    ft_messages(philosopher, DIED);
    philosopher->shared_data->simulation_running = false;
    
    return NULL;
}

void cleanup(t_data *data)
{
    int i = 0;

    if (data->forks)
    {
        while (i < data->num_philosophers)
        {
            pthread_mutex_destroy(&data->forks[i].mutex);
            i++;
        }
        free(data->forks);
    }
    if (data->philosophers)
    {
        free(data->philosophers);
    }
}

void create_threads(t_data *data)
{
    int i = 0;

    if (data->num_philosophers == 1)
    {
        pthread_create(&data->philosophers[0].thread_id, NULL, single_philosopher_routine, &data->philosophers[0]);
    }
    else
    {
        while (i < data->num_philosophers)
        {
            pthread_create(&data->philosophers[i].thread_id, NULL, philosopher_routine, &data->philosophers[i]);
            i++;
        }
        pthread_create(&data->monitor_thread, NULL, monitor_routine, data);
    }
}

void join_threads(t_data *data)
{
    int i = 0;

    while (i < data->num_philosophers)
    {
        pthread_join(data->philosophers[i].thread_id, NULL);
        i++;
    }
    if (data->num_philosophers > 1)
    {
        pthread_join(data->monitor_thread, NULL);
    }
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
    {
        printf("Error, correct input example: 5 800 200 200 [8]\n");
        return 1;
    }

    validate_and_store_args(argc, argv, &data);
    initialise_forks(&data);
    init_philosophers(&data);

    data.start_time = get_current_timestamp(NULL);
    data.simulation_running = true;

    create_threads(&data);
    join_threads(&data);
    cleanup(&data);

    return 0;
}


/* int main(int argc, char **argv) 
{
    t_data data;
    pthread_t monitor_thread;
    int i;
    i = 0;

    if (argc != 5 && argc != 6) 
    {
        printf("Error, correct input example: 5 800 200 200 [8]\n");
        return 1;
    }

    validate_and_store_args(argc, argv, &data);
    initialise_forks(&data);
    init_philosophers(&data);

    data.start_time = get_current_timestamp(NULL);
    data.simulation_running = true;

    if (data.num_philosophers == 1) 
    {
        pthread_create(&data.philosophers[0].thread_id, NULL, single_philosopher_routine, &data.philosophers[0]);
    } 
    else 
    {
        while (i < data.num_philosophers) 
        {
            pthread_create(&data.philosophers[i].thread_id, NULL, philosopher_routine, &data.philosophers[i]);
            i++;
        }
        pthread_create(&monitor_thread, NULL, monitor_routine, &data);
    }

    i = 0; // Reset i for reuse
    while (i < data.num_philosophers) 
    {
        pthread_join(data.philosophers[i].thread_id, NULL);
        i++;
    }
    if (data.num_philosophers > 1) 
    {
        pthread_join(monitor_thread, NULL);
    }

    cleanup(&data);

    return 0;
} */
