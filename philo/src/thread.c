/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/06/01 16:16:26 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The main routine of the philos, eating, sleeping and thinking
*/
void	*routine(void *void_philo)
{
	t_data	*data;
	t_philo	*philo;

	data = call_struct();
	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2 == 0)
		usleep(15000);
	while (1)
	{
		if (check_full() == 1)
			break ;
		pthread_mutex_lock(&data->mutex.change_state);
		if (data->dead == true)
		{
			pthread_mutex_unlock(&data->mutex.change_state);
			break ;
		}
		pthread_mutex_unlock(&data->mutex.change_state);
		philo_eating(philo);
		print_action(philo->philo_id, time_stamp(), PHILO_THINKING);
	}
	return (NULL);
}

/**
 * Waits until every thread is finished
*/
void	wait_thread(void)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		if (pthread_detach(philo->thread_id) == -1)
			break ;
		i++;
	}
}

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
		if (pthread_create(&philo->thread_id, NULL, routine, philo) == -1)
			return ;
		i++;
	}
	wait_thread();
	check_death();
}
