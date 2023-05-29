/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:38:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/29 14:31:01 by acouture         ###   ########.fr       */
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

/**
 * Checks if the time of last meal is greater than the time_to_die
*/
int	check_death(void)
{
	int		time_check;
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = -1;
	data = call_struct();
	while (++i < data->nb_philo)
	{
		philo = &data->philo[i];
		pthread_mutex_lock(&data->mutex.last_meal);
		time_check = time_stamp() - philo->time_last_meal;
		pthread_mutex_unlock(&data->mutex.last_meal);
		if (time_check >= data->time_to_die || death_conditions() == 1)
		{
			pthread_mutex_lock(&data->mutex.change_state);
			if (data->dead == false)
				printf("%llu ms Philo %d %s\n", (time_stamp()
						- data->start_time), philo->philo_id, PHILO_DEAD);
			data->dead = true;
			pthread_mutex_unlock(&data->mutex.change_state);
			return (1);
		}
	}
	return (0);
}

int death_conditions(void)
{
	t_data *data;

	data = call_struct();
	if ((data->nb_philo % 2 == 0) && (data->time_to_die < (data->time_to_eat * 2)))
		return (1);
	else if ((data->nb_philo % 2 != 0) && (data->time_to_die < (data->time_to_eat * 3)))
		return (1);
	return (0);
}
