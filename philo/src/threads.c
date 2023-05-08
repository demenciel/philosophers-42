/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/08 17:19:16 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;

	data = call_struct();
	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2 == 0)
		my_sleep(data->time_to_eat);
	check_death();
	while (data->dead == false && data->all_ate == false)
	{
		if (data->must_eat && philo->philo_id == data->nb_of_philo)
		{
			if (philo->nb_time_eat == data->must_eat)
				data->all_ate = true;
		}
		philo_forks(philo);
		print_action(philo->philo_id, PHILO_SLEEPING);
		my_sleep(data->time_to_sleep);
		print_action(philo->philo_id, PHILO_THINKING);
	}
	return (NULL);
}

int	wait_thread(void)
{
	int	i;
	t_data *data;

	i = 0;
	data = call_struct();
	while (i < call_struct()->nb_of_philo)
	{
		pthread_join(call_struct()->philo[i].thread_id, NULL);
		if (data->all_ate)
			return (1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_death(void)
{
	int		i;
	int		nb_philo;
	int		time_to_die;
	int		time_check;
	t_philo	*philo;

	i = 0;
	nb_philo = call_struct()->nb_of_philo;
	time_to_die = call_struct()->time_to_die;
	pthread_mutex_lock(&call_struct()->death_checker);
	while (i < nb_philo)
	{
		philo = &call_struct()->philo[i];
		time_check = time_stamp() - philo->time_last_meal;
		if (time_check > time_to_die)
		{
			print_action(philo->philo_id, PHILO_DEAD);
			call_struct()->dead = true;
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	pthread_mutex_unlock(&call_struct()->death_checker);
	return (EXIT_SUCCESS);
}

int	launch_philo(void)
{
	int i = 0;
	t_philo *philo;

	init_philo();
	init_mutex();
	call_struct()->start_time = time_stamp();
	while (i < call_struct()->nb_of_philo)
	{
		philo = &call_struct()->philo[i];
		philo->time_last_meal = time_stamp();
		if (pthread_create(&philo->thread_id, NULL, routine, philo) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	if (wait_thread() != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}