#include "philo.h"

void check_death_condition(t_data *data, int *all_philosophers_satisfied)
{
    int i = 0;
    while (i < data->num_philosophers)
    {
        if (philosopher_is_dead(&data->philosophers[i]))
        {
            data->simulation_running = false;
            ft_messages(&data->philosophers[i], DIED);
            *all_philosophers_satisfied = 0; // Ensure loop in monitor_routine breaks
            break;
        }
        i++;
    }
}

void check_meal_satisfaction(t_data *data, int *all_philosophers_satisfied)
{
    int i = 0;
    *all_philosophers_satisfied = 1; // Assume true until proven otherwise
    if (data->num_meals_required > 0)
    {
        while (i < data->num_philosophers)
        {
            if (data->philosophers[i].meals_eaten < data->num_meals_required)
            {
                *all_philosophers_satisfied = 0;
                break;
            }
            i++;
        }
    }
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int all_philosophers_satisfied;

    while (data->simulation_running)
    {
        check_death_condition(data, &all_philosophers_satisfied);
        if (!data->simulation_running) 
            break ;

        check_meal_satisfaction(data, &all_philosophers_satisfied);
        if (data->num_meals_required > 0 && all_philosophers_satisfied)
        {
            data->simulation_running = false;
        }

        usleep(500); // Adjust sleep time if necessary
    }
    return NULL;
}

