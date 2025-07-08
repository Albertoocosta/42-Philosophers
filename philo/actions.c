/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:42 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/08 12:07:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_eat(t_philo_data *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->lfork);
	else
		pthread_mutex_lock(philo->rfork);
	print_philo(philo, "has taken a fork");
	if (philo->data->nphilo == 1)
	{
		usleep((philo->data->tdie + 10) * 1000);
		pthread_mutex_unlock(philo->lfork);
		return (NULL);
	}
	else
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->rfork);
		else
			pthread_mutex_lock(philo->lfork);
		print_philo(philo, "has taken a fork");
	}
	aux_philo_eat(philo);
	return (NULL);
}

static int	all_philos_ok(t_philo *time, t_philo_data *philo, int *total)
{
	int	i;

	i = 0;
	while (i < time->nphilo)
	{
		if (check_if_is_death(&philo[i]) == 1)
			return (1);
		if (eat_all(&philo[i]))
			(*total)++;
		i++;
	}
	return (0);
}

void	*check_death(t_philo *time, t_philo_data *philo)
{
	int	total;

	total = 0;
	while (1)
	{
		usleep(1000);
		if (all_philos_ok(time, philo, &total) == 1)
			return (NULL);
		if (total == time->nphilo)
		{
			pthread_mutex_lock(&philo->data->death);
			philo->data->isdprint = 1;
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
	}
}

int	check_if_is_death(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (get_time() - philo->lastmeal > philo->data->tdie)
	{
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_lock(&philo->data->print);
		printf("%i %i died\n", get_time() - philo->data->startime,
			philo->id + 1);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->data->death);
		philo->data->isdprint = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal);
	return (0);
}

int	eat_all(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->numeal);
	if (philo->data->tmusteat != -1 && philo->nmeals >= philo->data->tmusteat)
	{
		pthread_mutex_unlock(&philo->numeal);
		return (1);
	}
	pthread_mutex_unlock(&philo->numeal);
	return (0);
}
