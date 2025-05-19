#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define FORK_TAKEN 0
#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DIED 4

typedef struct s_fork {
    int id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_data t_data;

typedef struct s_philo {
    int id;
    unsigned long last_meal;
    int left_fork_id;
    int right_fork_id;
    int meals_eaten;
    pthread_t thread_id;
    t_data *shared_data;
    unsigned long time_to_eat;    
    unsigned long time_to_sleep;  
    unsigned long time_to_die;    
} t_philo;

struct s_data {
    int num_philosophers;
    unsigned long time_to_die;
    unsigned long time_to_eat;
    unsigned long time_to_sleep;
    int num_meals_required;
    t_fork *forks;
    t_philo *philosophers;
    bool simulation_running;
    pthread_mutex_t write_mutex;
    unsigned long start_time;
    pthread_t monitor_thread;
};

void *philosopher_routine(void *arg);
long ft_atol(const char *str);
int is_valid_int(const char *str);
void validate_and_store_args(int argc, char **argv, t_data *data);
void initialise_forks(t_data *data);
void init_philosophers(t_data *data);
void *monitor_routine(void *arg);
unsigned long get_current_timestamp(t_data *data);
bool philosopher_is_dead(t_philo *philosopher);
int ft_usleep(unsigned long time);
size_t get_current_time(void);
unsigned long get_time(void);
void ft_messages(t_philo *philosopher, int state);

#endif
