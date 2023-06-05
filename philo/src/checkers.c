/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:38:21 by acouture          #+#    #+#             */
/*   Updated: 2023/06/05 16:14:30 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * By multiplying the number of philo and the number of times each must eat,
	compares the result with total of times eating was executed
*/
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

void	declare_death(t_data *data, int id)
{
	pthread_mutex_lock(&data->mutex.change_state);
	if (data->dead == false)
		printf("%llu ms Philo %d %s\n", (time_stamp() - data->start_time), id,
			PHILO_DEAD);
	data->dead = true;
	pthread_mutex_unlock(&data->mutex.change_state);
}

/**
 * Checks if the time of last meal is greater than the time_to_die
*/
int	check_death(void)
{
	int		time_check;
	int		i;
	t_philo	*philo;
	t_data	*data;

	data = call_struct();
	while (1)
	{
		if (check_full() == 1)
			break ;
		i = -1;
		while (++i < data->nb_philo)
		{
			philo = &data->philo[i];
			pthread_mutex_lock(&data->mutex.last_meal);
			time_check = time_stamp() - philo->time_last_meal;
			pthread_mutex_unlock(&data->mutex.last_meal);
			if (time_check >= data->time_to_die)
			{
				declare_death(data, philo->philo_id);
				return (1);
			}
		}
	}
	return (0);
}
