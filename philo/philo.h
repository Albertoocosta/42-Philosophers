/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:01:03 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/09 22:54:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				tmusteat;
	int				isdead;
	int				isdprint;
	int				startime;
	pthread_t		*id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}					t_philo;

typedef struct s_philo_data
{
	int				id;
	int				nmeals;
	int				lastmeal;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	numeal;
	pthread_mutex_t	meal;
	t_philo			*data;
}					t_philo_data;

// routine
void	start_philo(t_philo_data *philo, t_philo *time);
void	init_struct(t_philo *time);
void	init_mutex(t_philo *time);
void	destroy_mutex(t_philo *time, t_philo_data *philo);
// routine 2
void	print_philo(t_philo_data *philo, char *str);
int		get_time(void);
void	set_lastmeal(t_philo_data *philo);
// init
int		set_args(char **av, t_philo *time);
int		is_formatted(char **av, int ac, t_philo *time);
void	create_pthreads(t_philo *time, t_philo_data *philo);
int		init_philos(t_philo *time);
void	*run_philos(void *arg);
// actions
void	*philo_eat(t_philo_data *philo);
void	*check_death(t_philo *time, t_philo_data *philo);
int		check_if_is_death(t_philo_data *philo);
int		eat_all(t_philo_data *philo);

//utils
int		check_num(char *str);
void	*philo_sleep(t_philo_data *philo);
void	aux_philo_eat(t_philo_data *philo);
void	ft_usleep(int time_to_wait, t_philo_data *philo);

#endif