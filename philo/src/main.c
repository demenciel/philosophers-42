/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:44:15 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 14:23:31 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
}

void	*philo_start(void *philo_th)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_th;

	if (call_struct()->start_time == 0)
		call_struct()->start_time = time_stamp();
	while (philo->is_dead == false)
	{
		philo_eating(philo);
		pthread_mutex_lock(&call_struct()->sleeping);
		print_action(time_stamp(), philo->philo_id, PHILO_SLEEPING);
		usleep(call_struct()->time_to_sleep);
		pthread_mutex_unlock(&call_struct()->sleeping);
		print_action(time_stamp(), philo->philo_id, PHILO_THINKING);
	}
	return (NULL);
}

void	launch_philo(void)
{
	int	i;
	i = 0;

	while (i < call_struct()->nb_of_philo)
	{
		pthread_create(&call_struct()->philo[i].thread_id,
						NULL,
						philo_start,
						&call_struct()->philo[i]);
		i++;
	}
	i = 0;
	while (i < call_struct()->nb_of_philo)
	{
		if (pthread_join(call_struct()->philo[i].thread_id, NULL) != 0)
			return ;
		i++;
	}
	if (check_for_death() == 1)
		return ;
}

int	main(int ac, char **av)
{
	if (check_av(av, ac) == 1 || ac < 5)
		return (1);
	else
	{
		init_all(av);
		launch_philo();
	}
}