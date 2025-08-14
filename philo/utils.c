/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:34:54 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/14 16:04:52 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	aux_philo_eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&philo->meal);
	print_philo(philo, "eating");
	ft_usleep(philo->data->teat * 1);
	pthread_mutex_lock(&philo->numeal);
	philo->nmeals++;
	pthread_mutex_unlock(&philo->numeal);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
	else
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
}

void	*philo_sleep(t_philo_data *philo)
{
	print_philo(philo, "sleeping");
	ft_usleep(philo->data->tsleep * 1);
	print_philo(philo, "thinking");
	ft_usleep(1);
	return (NULL);
}

void	ft_usleep(int time_to_wait)
{
	int	start;

	start = get_time();
	while (get_time() - start < time_to_wait)
		usleep(100);
}
