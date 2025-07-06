#include "philo.h"

void	print_philo(t_philo_data *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->isdprint == 1)\
	{
		pthread_mutex_unlock(&philo->data->death);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	printf("%i %i %s\n", get_time() - philo->data->startime, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	get_time(void)
{
	struct timeval currentTime;
	
	if (gettimeofday(&currentTime, NULL) != 0)
		return (printf("Get time error"), 0);
	return ((currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000));
}

void	set_lastmeal(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&philo->meal);
}