/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/05/19 12:16:28 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The routine being executed by each philosopher
 * Eating, sleeping, thinking
*/
void	*routine(void *param)
{
	t_philo	*philo;
	t_data	*data;
	bool	full;
	bool	dead;

	philo = (t_philo *)param;
	data = call_struct();
	if (philo->philo_id % 2 == 0)
		usleep(data->time_to_eat * 500);
	pthread_mutex_lock(&data->mutex.check_full);
	full = data->full;
	dead = data->dead;
	pthread_mutex_unlock(&data->mutex.check_full);
	while (!full)
	{
		if (check_full() == 1)
			return (NULL);
		if (check_death() == 1)
			return (NULL);
		print_action(philo->philo_id, time_stamp(), PHILO_THINKING);
		philo_fork(philo);
		if (!dead)
			philo_sleeping(philo);
	}
	return (NULL);
}

/**
 * Waits for each of the threads to be completed
*/
void	wait_thread(void)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		pthread_join(philo->thread_id, NULL);
		i++;
	}
}

/**
 * Creates and launches all of the threads
*/
void	launcher(void)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	data = call_struct();
	data->start_time = time_stamp();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		pthread_mutex_lock(&data->mutex.last_meal);
		stamp_last_meal();
		pthread_mutex_unlock(&data->mutex.last_meal);
		pthread_create(&philo->thread_id, NULL, routine, philo);
		i++;
	}
	check_full();
	if (check_death() == 1)
		return ;
	wait_thread();
}
