/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:01:07 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/09 22:54:35 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_philo_data *philo, t_philo *time)
{
	int	i;

	i = 0;
	while (i < time->nphilo)
	{
		pthread_mutex_init(&philo[i].meal, NULL);
		pthread_mutex_init(&philo[i].numeal, NULL);
		philo[i].id = i;
		philo[i].data = time;
		philo[i].lastmeal = get_time();
		philo[i].nmeals = 0;
		philo[i].lfork = &time->forks[i];
		if (i == time->nphilo - 1)
			philo[i].rfork = &time->forks[0];
		else
			philo[i].rfork = &time->forks[i + 1];
		i++;
	}
}

void	init_struct(t_philo *time)
{
	time->nphilo = 0;
	time->tdie = 0;
	time->teat = 0;
	time->tsleep = 0;
	time->tmusteat = -1;
	time->isdead = 0;
	time->isdprint = 0;
	time->startime = 0;
}

void	init_mutex(t_philo *time)
{
	int	i;

	i = 0;
	pthread_mutex_init(&time->print, NULL);
	pthread_mutex_init(&time->death, NULL);
	while (i < time->nphilo)
	{
		pthread_mutex_init(&time->forks[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_philo *time, t_philo_data *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&time->print);
	pthread_mutex_destroy(&time->death);
	while (i < time->nphilo)
	{
		pthread_mutex_destroy(&philo[i].meal);
		pthread_mutex_destroy(&philo[i].numeal);
		pthread_mutex_destroy(&time->forks[i]);
		i++;
	}
	free(time->id);
	free(time->forks);
}
