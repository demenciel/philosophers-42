/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:34:52 by acouture          #+#    #+#             */
/*   Updated: 2023/05/23 12:46:24 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_all(char **av)
{
	init_args(av);
	init_philo();
	if (init_mutex() != 0)
		return (1);
	if (check_av_values() != 0)
		return (1);
	return (0);
}

void	init_args(char **av)
{
	t_data	*data;

	data = call_struct();
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->must_eat = ft_atoi(av[5]);
		data->must_eat *= data->nb_philo;
	}
	else
		data->must_eat = 0;
	data->total_eaten = 0;
	data->dead = false;
	data->full = false;
	data->last_meal_stamped = false;
}

void	init_philo(void)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		philo->philo_id = (i + 1);
		i++;
	}
}

int	init_mutex(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->mutex.fork[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_init(&data->mutex.print, NULL);
	pthread_mutex_init(&data->mutex.last_meal, NULL);
	pthread_mutex_init(&data->mutex.change_state, NULL);
	pthread_mutex_init(&data->mutex.check_full, NULL);
	pthread_mutex_init(&data->mutex.nb_eat_mutex, NULL);
	return (0);
}

void	destroy_mutex(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex.fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex.check_full);
	pthread_mutex_destroy(&data->mutex.print);
	pthread_mutex_destroy(&data->mutex.last_meal);
	pthread_mutex_destroy(&data->mutex.change_state);
	pthread_mutex_destroy(&data->mutex.nb_eat_mutex);
}
