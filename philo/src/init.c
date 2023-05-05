/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:16 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 14:22:36 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_all(char **av)
{
	init_data(av);
	init_mutex();
	init_philo();
}

void	init_data(char **av)
{
	call_struct()->nb_of_philo = ft_atoi(av[1]);
	call_struct()->time_to_die = ft_atoi(av[2]);
	call_struct()->time_to_eat = ft_atoi(av[3]);
	call_struct()->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		call_struct()->must_eat = ft_atoi(av[5]);
	else
		call_struct()->must_eat = 0;
}

void	init_mutex()
{
	int i;

	i = call_struct()->nb_of_philo;
	while (i)
	{
		pthread_mutex_init(&call_struct()->fork[i], NULL);
		i--;
	}
	pthread_mutex_init(&call_struct()->fork_access, NULL);
	pthread_mutex_init(&call_struct()->eating, NULL);
	pthread_mutex_init(&call_struct()->sleeping, NULL);
}

void	init_philo()
{
	int i;

	i = 0;
	while (i < call_struct()->nb_of_philo)
	{
		call_struct()->philo[i].is_dead = false;
		call_struct()->philo[i].nb_time_eat = 0;
		call_struct()->philo[i].philo_id = i + 1;
		i++;
	}
}