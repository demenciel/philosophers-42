/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:57:39 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 13:47:39 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Depending on the number of total philo,
	Philo will take the appropriate fork on the left
*/
pthread_mutex_t	*take_fork1(t_philo *philo)
{
	t_data			*data;
	pthread_mutex_t	*fork1;

	data = call_struct();
	if ((philo->philo_id) - 1 < ((philo->philo_id) % data->nb_philo))
		fork1 = &data->mutex.fork[philo->philo_id - 1];
	else
		fork1 = &data->mutex.fork[(philo->philo_id) % data->nb_philo];
	pthread_mutex_lock(fork1);
	if (check_death() != 1)
		print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
	else
		pthread_mutex_unlock(fork1);

	return (fork1);
}

/**
 * Depending on the number of total philo,
	Philo will take the appropriate fork on the right
*/
pthread_mutex_t	*take_fork2(t_philo *philo)
{
	t_data			*data;
	pthread_mutex_t	*fork2;

	data = call_struct();
	if ((philo->philo_id) - 1 < ((philo->philo_id) % data->nb_philo))
		fork2 = &data->mutex.fork[(philo->philo_id) % data->nb_philo];
	else
		fork2 = &data->mutex.fork[philo->philo_id - 1];
	pthread_mutex_lock(fork2);
	if (check_death() != 1)
		print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
	else
		pthread_mutex_unlock(fork2);
	return (fork2);
}

/**
 * After taking up the forks, begins eating and time stamps the meal
*/
int	philo_eating(t_philo *philo)
{
	t_data			*data;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	data = call_struct();
	fork1 = take_fork1(philo);
	fork2 = take_fork2(philo);
	print_action(philo->philo_id, time_stamp(), PHILO_EATING);
	pthread_mutex_lock(&data->mutex.last_meal);
	philo->time_last_meal = time_stamp();
	data->total_eaten++;
	pthread_mutex_unlock(&data->mutex.last_meal);
	my_sleep(data->time_to_eat);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	return (0);
}

/**
 * Begins the actions of sleeping for time_to_sleep of time
*/
void	philo_sleeping(t_philo *philo)
{
	t_data	*data;

	data = call_struct();
	my_sleep(data->time_to_sleep);
	print_action(philo->philo_id, time_stamp(), PHILO_SLEEPING);
}
