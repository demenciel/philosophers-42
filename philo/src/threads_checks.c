/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 17:10:19 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&call_struct()->eating);
	print_action(time_stamp(), philo->philo_id, PHILO_EATING);
	usleep(call_struct()->time_to_eat);
	pthread_mutex_unlock(&call_struct()->eating);
	return (0);
}