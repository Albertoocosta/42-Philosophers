#include "philo.h"

int	set_args(char **av, t_philo *time)
{
	time->nphilo = atoi(av[1]);
	if (time->nphilo <= 0)
		return	(printf("Not enough philosofers\n"), 1);
	time->tdie = atoi(av[2]);
	if (time->tdie <= 0)
		return (printf("Wrong time to die\n"), 1);
	time->teat = atoi(av[3]);
	if (time->teat <= 0)
		return (printf("Wrong time to eat\n"), 1);
	time->tsleep = atoi(av[4]);
	if (time->tsleep <= 0)
		return (printf("Wrong time to sleep\n"), 1);
	if (av[5])
	{
		time->tmusteat = atoi(av[5]);
		if (time->tmusteat <= 0)
			return (printf("Wrong time to each philo eats\n"), 1);
	}
	return (0);
}

int	is_formatted(char **av, int ac, t_philo *time)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosophers_must_eat]\n");
		return (1);
	}
	while (av[i])
	{
		if(check_num(av[i++]) == 1)
		{
			printf("%s is not a valid number \n", av[i - 1]);
			return (1);
		}
	}
	return (set_args(av, time));
}

void	create_pthreads(t_philo *time, t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < time->nphilo)
	{
		if (i % 2 == 0)
			pthread_create(&time->id[i], NULL, &run_philos, (void *)&philo[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < time->nphilo)
	{
		pthread_create(&time->id[i], NULL, &run_philos, (void *)&philo[i]);
		i += 2;
	}
	check_death(time, philo);
	i = 0;
	while (i < time->nphilo)
	{
		pthread_join(time->id[i], NULL);
		i++;
	}
}

int	init_philos(t_philo *time)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)malloc((time->nphilo) * sizeof(t_philo_data));
	time->id = (pthread_t *)malloc((time->nphilo) * sizeof(pthread_t));
	time->forks = (pthread_mutex_t *)malloc((time->nphilo) * sizeof(pthread_mutex_t));
	start_philo(philo, time);
	init_mutex(time);
	time->startime = get_time();
	create_pthreads(time, philo);
	destroy_mutex(time, philo);
	free(philo);
	return(0);
}

void	*run_philos(void *arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)arg;
	set_lastmeal(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->isdprint)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		philo_eat(philo);
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->isdprint)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		philo_sleep(philo);
	}
	return (0);
}
