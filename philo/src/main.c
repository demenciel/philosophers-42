/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:44:15 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 15:37:53 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
}

void	init_philo(t_philo *philo_struct)
{
	philo_struct->philo_id = 0;
	philo_struct->status = 0;
	philo_struct->nb_time_eat = 0;
}

void	init_data(char **av)
{
	call_struct()->nb_of_philo = ft_atoi(av[1]);
	call_struct()->time_to_die = ft_atoi(av[2]);
	call_struct()->time_to_eat = ft_atoi(av[3]);
	call_struct()->time_to_sleep = ft_atoi(av[4]);
	init_philo(call_struct()->philo);
	call_struct()->start_time = time_stamp();
}

void	*philo_actions(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	printf("Philo %d says hello in %d\n", philo->philo_id, time_to_action(time_stamp()));
	return (NULL);
}

void	launch(void)
{
	int	i;

	i = 1;
	while (i < (call_struct()->nb_of_philo + 1))
	{
		call_struct()->philo[i].philo_id = i;
		pthread_create(&(call_struct()->philo[i].thread_id), NULL,
				philo_actions, &(call_struct()->philo[i]));
		pthread_join((call_struct()->philo[i].thread_id), NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 5)
	{
		if (check_av(av, ac) == 1)	
			return (1);
		init_data(av);
		launch();
	}
	else
		return (1);
	return (0);
}