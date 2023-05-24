/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:38:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 13:26:26 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_full(void)
{
	t_data	*data;
	int		total;

	data = call_struct();
	if (data->must_eat)
	{
		pthread_mutex_lock(&data->mutex.last_meal);
		total = data->total_eaten;
		pthread_mutex_unlock(&data->mutex.last_meal);
		if (total >= data->must_eat)
			return (1);
	}
	return (0);
}

int	check_death(void)
{
	int		time_check;
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		pthread_mutex_lock(&data->mutex.last_meal);
		time_check = time_stamp() - philo->time_last_meal;
		pthread_mutex_unlock(&data->mutex.last_meal);
		if (time_check >= data->time_to_die)
		{
			print_action(philo->philo_id, time_stamp(), PHILO_DEAD);
			pthread_mutex_lock(&data->mutex.change_state);
			data->dead = true;
			pthread_mutex_unlock(&data->mutex.change_state);
			return (1);
		}
		i++;
	}
	return (0);
}
