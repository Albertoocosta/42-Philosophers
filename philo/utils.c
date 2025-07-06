/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:34:54 by alberto           #+#    #+#             */
/*   Updated: 2025/07/07 00:31:13 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char *str)
{
	int i;
	
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
	usleep(philo->data->teat * 1000);
	pthread_mutex_lock(&philo->numeal);
	philo->nmeals++;
	pthread_mutex_unlock(&philo->numeal);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	*philo_sleep(t_philo_data *philo)
{
	print_philo(philo, "sleeping");
	usleep(philo->data->tsleep * 1000);
	print_philo(philo, "thinking");
	return (NULL);
}
