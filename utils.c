#include "philo.h"

int is_valid_int(const char *str)
 {
    if (*str == '+' || *str == '-') 
    {
        str++;
    }
    if (*str == '\0')
    {
        return (0);
    }
    while (*str) 
    {
        if (*str < '0' || *str > '9') 
        {
            return (0); 
        }
        str++;
    }

    return (1);
}

long	ft_atol(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}