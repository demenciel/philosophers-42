/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:44:15 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 16:50:48 by acouture         ###   ########.fr       */
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

void	*philo_actions(void *void_philo)
{
	t_philo	*philo;
	pthread_mutex_t	fork1;
	pthread_mutex_t	fork2;
	
	philo = (t_philo *)void_philo;
	// initialize fork 1
	fork1 = call_struct()->fork[philo->philo_id];
	// initialize fork 2
	if (philo->philo_id == 1)
		fork2 = call_struct()->fork[call_struct()->nb_of_philo];
	else
		fork1 = call_struct()->fork[philo->philo_id - 1];
	pthread_mutex_lock(&fork1);
	printf("%d Philo %d %s\n", time_to_action(time_stamp()), philo->philo_id,
			FORK_TAKEN);
	pthread_mutex_lock(&(call_struct()->fork[philo->philo_id + 1]));
	printf("%d Philo %d %s\n", time_to_action(time_stamp()), philo->philo_id,
			FORK_TAKEN);
	return (NULL);
}

void	launch(void)
{
	int	i;

	i = 1;
	while (i < (call_struct()->nb_of_philo + 1))
	{
		// sets philo id to i
		call_struct()->philo[i].philo_id = i;
		// sets fork id to i
		if (pthread_mutex_init(&(call_struct()->fork[i]), NULL) == 0)
			call_struct()->philo->fork_id = i;
		// creates the thread and passes the function to exec
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
		if (init_data(av) == 1)
			return (1);
		launch();
	}
	else
		return (1);
	return (0);
}