/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:16 by acouture          #+#    #+#             */
/*   Updated: 2023/05/02 15:08:50 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_all(char **av)
{
	if (init_data(av) == 1)
		return (1);
	if (init_mutex() == 1)
		return (1);
	return (0);
}

int	init_mutex(void)
{
	int	i;

	i = call_struct()->nb_of_philo;
	while (i)
	{
		if (pthread_mutex_init(&(call_struct()->fork[i]), NULL) == 1)
			return (1);
		i--;
	}
	pthread_mutex_init(&call_struct()->eating, NULL);
    pthread_mutex_init(&call_struct()->fork_access, NULL);
	return (0);
}

void	init_philo(t_philo *philo_struct)
{
	philo_struct->philo_id = 0;
	philo_struct->nb_time_eat = 0;
	philo_struct->time_last_meal = 0;
}

int	init_data(char **av)
{
	call_struct()->nb_of_philo = ft_atoi(av[1]);
	if (call_struct()->nb_of_philo <= 1)
		return (1);
	call_struct()->time_to_die = ft_atoi(av[2]);
	call_struct()->time_to_eat = ft_atoi(av[3]);
	call_struct()->time_to_sleep = ft_atoi(av[4]);
	if ((call_struct()->time_to_die <= call_struct()->time_to_eat))
		return (1);
	if (call_struct()->time_to_die <= call_struct()->time_to_sleep)
		return (1);
	init_philo(call_struct()->philo);
	// stamps the start of the program
	call_struct()->start_time = time_stamp();
	return (0);
}