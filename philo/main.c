#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	time;

	init_struct(&time);
	if (is_formatted(av, ac, &time) != 0)
		return (1);
	if (init_philos(&time))
		return (1);
}