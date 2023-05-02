/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:44:15 by acouture          #+#    #+#             */
/*   Updated: 2023/05/02 15:44:59 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
}

void	*philo_actions(void *void_philo)
{
	t_philo	*philo;
	

	philo = (t_philo *)void_philo;
	while (philo->is_dead == false)
	{
		// starts eating
		if (philo_eating(philo) != 0)
			return (NULL);
		// sleeps
		print_action(time_stamp(), philo->philo_id, PHILO_SLEEPING);
		usleep(call_struct()->time_to_sleep);
		// Thinks
		print_action(time_stamp(), philo->philo_id, PHILO_THINKING);
	}
	return (NULL);
}

void	wait_thread()
{
	t_philo *philo;
	int i = 0;

	while (i < call_struct()->nb_of_philo)
	{
		philo = &call_struct()->philo[i];
		pthread_join(philo->thread_id, NULL);
		i++;
	}
	pthread_join(call_struct()->monitor_thread, NULL);
}

void	launch(void)
{
	int	i;
	pthread_t monitor_thread;

	i = 1;
	while (i < (call_struct()->nb_of_philo + 1))
	{
		// sets philo id to i
		call_struct()->philo[i].philo_id = i;
		// creates the thread and passes the function to exec
		pthread_create(&(call_struct()->philo[i].thread_id), NULL,
				philo_actions, &(call_struct()->philo[i]));
		i++;
	}
	pthread_create(&monitor_thread, NULL, checks_for_death, NULL);
	wait_thread();
}

/**
 * @param av Time_to_die, time_to_eat, time_to_sleep
*/
int	main(int ac, char **av)
{
	if (ac == 5)
	{
		if (init_all(av) == 1)
			return (1);
		launch();
	}
	else
		return (1);
	return (0);
}