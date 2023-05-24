/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:38:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 10:10:22 by acouture         ###   ########.fr       */
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
	int			i;
	t_data		*data;
	t_philo		*philo;
	int	last_meal;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
        philo = &data->philo[i];
        pthread_mutex_lock(&data->mutex.last_meal);
		last_meal = time_stamp() - philo->time_last_meal;
		pthread_mutex_unlock(&data->mutex.last_meal);
        if (last_meal >= data->must_eat)
        {
            printf("%d ms Philo %d %s\n", last_meal, philo->philo_id, PHILO_DEAD);
            return (1);
        }
        i++;
	}
	return (0);
}

// void	lock_dead(void)
// {
// 	t_data	*data;

// 	data = call_struct();
// 	pthread_mutex_lock(&data->mutex.change_state);
// 	data->dead = true;
// 	pthread_mutex_unlock(&data->mutex.change_state);
// }
