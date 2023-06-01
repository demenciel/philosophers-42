/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:57:39 by acouture          #+#    #+#             */
/*   Updated: 2023/06/01 16:10:59 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * After taking up the forks, begins eating and time stamps the meal
*/
int	philo_eating(t_philo *philo)
{
	t_data	*data;

	data = call_struct();
	if (pthread_mutex_lock(&data->mutex.fork[philo->l_fork]) != 0)
		return (1);
	print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
	if (pthread_mutex_lock(&data->mutex.fork[philo->r_fork]) != 0)
		return (1);
	print_action(philo->philo_id, time_stamp(), FORK_TAKEN);
	print_action(philo->philo_id, time_stamp(), PHILO_EATING);
	pthread_mutex_lock(&data->mutex.last_meal);
	philo->time_last_meal = time_stamp();
	data->total_eaten++;
	pthread_mutex_unlock(&data->mutex.last_meal);
	my_sleep(data->time_to_eat);
	if (pthread_mutex_unlock(&data->mutex.fork[philo->l_fork]) != 0)
		return (1);
	if (pthread_mutex_unlock(&data->mutex.fork[philo->r_fork]) != 0)
		return (1);
	my_sleep(data->time_to_sleep);
	print_action(philo->philo_id, time_stamp(), PHILO_SLEEPING);
	return (0);
}
