/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/05/23 12:49:42 by acouture         ###   ########.fr       */
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

	philo = (t_philo *)param;
	data = call_struct();
	if (philo->philo_id % 2 == 0)
		my_sleep(data->time_to_eat / 2);
	while (1)
	{
		if (check_full() == 1)
			return (NULL);
		if (check_death() == 1)
			return (NULL);
		philo_fork(philo);
		philo_sleeping(philo);
		print_action(philo->philo_id, time_stamp(), PHILO_THINKING);
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
	pthread_mutex_lock(&data->mutex.last_meal);
	stamp_last_meal();
	pthread_mutex_unlock(&data->mutex.last_meal);
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		pthread_create(&philo->thread_id, NULL, routine, philo);
		i++;
	}
	if (check_full() == 1)
		return ;
	if (check_death() == 1)
		return ;
	wait_thread();
}
