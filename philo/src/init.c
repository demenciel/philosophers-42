/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:34:52 by acouture          #+#    #+#             */
/*   Updated: 2023/05/27 09:05:15 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Initialize everything
*/
int	init_all(char **av)
{
	init_args(av);
	create_philos();
	if (init_mutex() != 0)
		return (1);
	if (check_av_values() != 0)
		return (1);
	return (0);
}

/**
 * Converts each av in a number and initialize the struct's parameters
*/
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
}

/**
 * Using loop, initialize the parameters in each philo struct 
*/
void	create_philos(void)
{
	int		i;
	int		j;
	t_data	*data;

	i = 0;
	j = 1;
	data = call_struct();
	while (j < data->nb_philo)
	{
		fill_philo_struct(data, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo_struct(data, i, j);
}

void	fill_philo_struct(t_data *data, int i, int j)
{
	data->philo[i].philo_id = i + 1;
	data->philo[i].l_fork = i;
	data->philo[i].r_fork = j;
	data->philo[i].time_last_meal = time_stamp();
}

/**
 * Initialize every mutexes needed
*/
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
	return (0);
}
