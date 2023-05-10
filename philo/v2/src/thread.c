/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/05/10 16:19:58 by acouture         ###   ########.fr       */
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
		usleep(data->time_to_eat * 500);
	while (check_death() == 0 && !data->full)
	{
		if (check_full() == 1)
			return (NULL);
		philo_fork(philo);
		if (check_death() != 1)
			philo_sleeping(philo);
		print_action(philo->philo_id, time_stamp(), PHILO_THINKING);
	}
	return (NULL);
}

/**
 * If arg[5] is present,
	checks if every philo as eaten for args[5] amount of time
*/
int	check_full(void)
{
	t_data	*data;
	t_philo	*philo;

	data = call_struct();
	philo = &data->philo[data->nb_philo - 1];
	if (data->must_eat)
	{
		if (philo->nb_eat == data->must_eat)
		{
			data->full = true;
			return (1);
		}
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
		pthread_mutex_lock(&call_struct()->mutex.death_mutex);
		time_check = time_stamp() - philo->time_last_meal;
		pthread_mutex_unlock(&call_struct()->mutex.death_mutex);
		if (time_check >= call_struct()->time_to_die)
		{
			print_action(philo->philo_id, time_stamp(), PHILO_DEAD);
			call_struct()->dead = true;
			return (1);
		}
		i++;
	}
	return (0);
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
	int i;
	t_data *data;
	t_philo *philo;

	i = 0;
	data = call_struct();
	data->start_time = time_stamp();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		philo->time_last_meal = time_stamp();
		pthread_create(&philo->thread_id, NULL, routine, philo);
		i++;
	}
	check_death();
	check_full();
	wait_thread();
}