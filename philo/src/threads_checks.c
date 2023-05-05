/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 14:24:49 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eating(t_philo *philo)
{
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo_id = philo->philo_id;
	if (philo_id % 2 == 1)
		usleep(10);
    left_fork = &call_struct()->fork[philo_id];
    right_fork = &call_struct()->fork[(philo_id + 1) % (call_struct()->nb_of_philo + 1)];
	if (pthread_mutex_lock(right_fork) == 0)
		print_action(time_stamp(), philo->philo_id, FORK_TAKEN);
	if (pthread_mutex_lock(left_fork) == 0)
		print_action(time_stamp(), philo->philo_id, FORK_TAKEN);
	pthread_mutex_lock(&call_struct()->eating);
	print_action(time_stamp(), philo_id, PHILO_EATING);
	usleep(call_struct()->time_to_eat);
	philo->time_last_meal = time_stamp();
	philo->nb_time_eat++;
	pthread_mutex_unlock(&call_struct()->eating);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

int	check_for_death(void)
{
	int i;
	t_philo *philo;

	while (1)
	{
	    i = 0;
		if (call_struct()->philo[call_struct()->nb_of_philo].nb_time_eat == call_struct()->must_eat)
				return (1);
		while (i < call_struct()->nb_of_philo)
		{
			philo = &call_struct()->philo[i];
			if ((time_stamp() - philo[i].time_last_meal) >= call_struct()->time_to_die)
				return (1);
            i++;
		}
	}
	return (0);
}