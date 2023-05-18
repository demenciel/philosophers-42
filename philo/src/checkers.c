/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:38:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/18 17:27:36 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * If arg[5] is present,
	checks if every philo as eaten for args[5] amount of time
*/
int	check_full(void)
{
	t_data	*data;
	t_philo	*philo;
	int		nb_eat;
	int		i;

	data = call_struct();
	if (data->must_eat)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			philo = &data->philo[i];
			pthread_mutex_lock(&data->mutex.check_full);
			nb_eat = philo->nb_eat;
			pthread_mutex_unlock(&data->mutex.check_full);
			if (nb_eat < data->must_eat)
				break ;
			i++;
		}
		if (is_full(data, nb_eat) == 1)
			return (1);
	}
	return (0);
}

/**
 * Extension of check_full function
 * Checks if the number of times the philo as eaten is equal to must_eat if yes,
	returns 1 to exit function
*/
int	is_full(t_data *data, int nb_eat)
{
	if (nb_eat == data->must_eat)
	{
		pthread_mutex_lock(&data->mutex.check_full);
		data->full = true;
		pthread_mutex_unlock(&data->mutex.check_full);
		return (1);
	}
	return (0);
}

/**
 * For each philo,
	checks if the time since the last meal as exceeded time_to_die
*/
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
