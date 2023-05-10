/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:57:39 by acouture          #+#    #+#             */
/*   Updated: 2023/05/10 16:21:53 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * If no philo is dead or if the forks are correctly locked, philo eats
*/
void	philo_eating(t_philo *philo)
{
	t_data	*data;

	data = call_struct();
	pthread_mutex_lock(&data->mutex.eat);
	if (data->dead == false)
		print_action(philo->philo_id, time_stamp(), PHILO_EATING);
	philo->time_last_meal = time_stamp();
	pthread_mutex_unlock(&data->mutex.eat);
	if (check_death() != 1)
		my_sleep(data->time_to_eat);
}

/**
 * Depending on the philo,
	picks up the right forks for its position around the table
*/
void	philo_fork(t_philo *philo)
{
	t_data			*data;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	data = call_struct();
	fork1 = &data->mutex.fork[philo->philo_id - 1];
	fork2 = &data->mutex.fork[(philo->philo_id) % data->nb_philo];
	pthread_mutex_lock(fork1);
	if (check_death() != 1)
	{
		print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
		pthread_mutex_lock(fork2);
		print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
	}
	philo_eating(philo);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	philo->nb_eat++;
}

/**
 * Puts the thread to sleep for time_to_sleep amount of time
*/
void	philo_sleeping(t_philo *philo)
{
	t_data *data;

	data = call_struct();

	if (data->dead == false)
	{
		print_action(philo->philo_id, time_stamp(), PHILO_SLEEPING);
		my_sleep(data->time_to_sleep);
	}
}