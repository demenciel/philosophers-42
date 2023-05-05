/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:16 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 16:01:15 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_all(char **av)
{
	
	if (!init_args(av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_args(char **av)
{
	call_struct()->nb_of_philo = ft_atoi(av[1]);
	if (call_struct()->nb_of_philo <= 0)
		return (EXIT_FAILURE);
	call_struct()->time_to_die = ft_atoi(av[2]);
	if (call_struct()->time_to_die < 60)
		return (EXIT_FAILURE);
	call_struct()->time_to_eat = ft_atoi(av[3]);
	if (call_struct()->time_to_eat < 60)
		return (EXIT_FAILURE);
	call_struct()->time_to_sleep = ft_atoi(av[4]);
	if (call_struct()->time_to_sleep < 60)
		return (EXIT_FAILURE);
	if (av[5])
		call_struct()->must_eat = ft_atoi(av[5]);
	return (EXIT_SUCCESS);
}

void	init_philo()
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < call_struct()->nb_of_philo)
	{
		philo = &call_struct()->philo[i];
		philo->is_dead = false;
		philo->nb_time_eat = 0;
		philo->philo_id = i + 1;
		i++;
	}
}

void	init_mutex()
{
	int i;
	
	i = 0;
	while (i < call_struct()->nb_of_philo)
	{
		pthread_mutex_init(&call_struct()->fork[i], NULL);
		i++;
	}
}