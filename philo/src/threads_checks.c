/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/02 15:44:28 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_eating(t_philo *philo)
{
	int				time;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	if (philo->philo_id % 2 == 1)
		usleep(100);
	fork1 = &call_struct()->fork[philo->philo_id - 1];
	fork2 = &call_struct()->fork[philo->philo_id % call_struct()->nb_of_philo];
	if ((pthread_mutex_lock(&call_struct()->fork_access)) != 0)
		return (1);
	pthread_mutex_lock(fork1);
	print_action(time_stamp(), philo->philo_id, FORK_TAKEN);
	pthread_mutex_lock(fork2);
	print_action(time_stamp(), philo->philo_id, FORK_TAKEN);
	pthread_mutex_unlock(&call_struct()->fork_access);
	// begin eating after fork taken
	pthread_mutex_lock(&call_struct()->eating);
	time = time_stamp();
	print_action(time, philo->philo_id, PHILO_EATING);
	usleep(call_struct()->time_to_eat);
	philo->time_last_meal = time;
	pthread_mutex_unlock(&call_struct()->eating);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	philo->nb_time_eat++;
	return (0);
}

void	*checks_for_death(void *arg)
{
	(void)arg;
	t_philo *philo;
	int i;

	while (1)
	{
		philo = call_struct()->philo;
		i = 1;
		while (i < (call_struct()->nb_of_philo + 1))
		{
			if ((time_to_action(time_stamp())
					- philo[i].time_last_meal) >= call_struct()->time_to_die)
			{
				print_action(time_stamp(), philo[i].philo_id, PHILO_DEAD);
				philo->is_dead = true;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}