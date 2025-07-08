/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:01:10 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/08 12:23:30 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo_data *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->isdprint == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	printf("%i %i %s\n", get_time() - philo->data->startime,
		philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (printf("Get time error"), 0);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	set_lastmeal(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&philo->meal);
}
