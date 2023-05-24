/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 13:26:15 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *void_philo)
{
	t_data	*data;
	t_philo	*philo;

	data = call_struct();
	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2 == 0)
		my_sleep(data->time_to_eat);
	while (1)
	{
		if (check_full() == 1)
			break ;
		if (check_death() == 1)
			break ;
		philo_eating(philo);
		philo_sleeping(philo);
		print_action(philo->philo_id, time_stamp(), PHILO_THINKING);
	}
	return (NULL);
}

void	wait_thread(void)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	data = call_struct();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		if (pthread_join(philo->thread_id, NULL) == -1)
			break ;
		i++;
	}
}

void	launcher(void)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	data = call_struct();
	data->start_time = time_stamp();
	stamp_last_meal();
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		if (pthread_create(&philo->thread_id, NULL, routine, philo) == -1)
			return ;
		i++;
	}
	wait_thread();
}
