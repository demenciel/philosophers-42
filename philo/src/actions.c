/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:17 by acouture          #+#    #+#             */
/*   Updated: 2023/05/08 17:35:54 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_t	*eating;

	eating = &call_struct()->eating;
	pthread_mutex_lock(eating);
	print_action(philo->philo_id, PHILO_EATING);
	my_sleep(call_struct()->time_to_eat);
	philo->time_last_meal = time_stamp();
	philo->nb_time_eat++;
	pthread_mutex_unlock(eating);
}

void	philo_forks(t_philo *philo)
{
	int nb_philo;
	pthread_mutex_t *fork1;
	pthread_mutex_t *fork2;

	nb_philo = call_struct()->nb_of_philo;
	fork1 = &call_struct()->fork[philo->philo_id];
	fork2 = &call_struct()->fork[(philo->philo_id + 1) % nb_philo];

	pthread_mutex_lock(fork1);
	print_action(philo->philo_id, FORK_TAKEN);
	pthread_mutex_lock(fork2);
	print_action(philo->philo_id, FORK_TAKEN);
	philo_eating(philo);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}
