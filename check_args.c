#include "philo.h"

void validate_and_store_args(int argc, char **argv, t_data *data) {
    int i;
    long val;

    i = 1;
    while (i < argc) 
    {
        val = ft_atol(argv[i]);
        if (!is_valid_int(argv[i]) || val < INT_MIN || val > INT_MAX) 
        {
            printf("Error, correct input example: 5 800 200 200 [4]\n");
            return;
        }

        if (i == 1) data->num_philosophers = val;
        else if (i == 2) data->time_to_die = val;
        else if (i == 3) data->time_to_eat = val;
        else if (i == 4) data->time_to_sleep = val;
        else if (i == 5) data->num_meals_required = val;

        i++;
    }

    if (argc == 5)
     {
        data->num_meals_required = -1; // Default value if not specified
    }
}
