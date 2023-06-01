/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:20:35 by acouture          #+#    #+#             */
/*   Updated: 2023/06/01 16:10:51 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
}

/**
 * Destroys the mutexes
*/
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
	pthread_mutex_destroy(&data->mutex.print);
	pthread_mutex_destroy(&data->mutex.last_meal);
	pthread_mutex_destroy(&data->mutex.change_state);
}

/**
 * Checks that no av are under 60 ms
*/
int	check_av_values(void)
{
	t_data	*data;

	data = call_struct();
	if (data->time_to_die < 60)
		return (1);
	if (data->time_to_eat < 60)
		return (1);
	if (data->time_to_sleep < 60)
		return (1);
	if (data->nb_philo > 200)
		return (1);
	return (0);
}

/**
 * The main of the program
*/
int	main(int ac, char **av)
{
	if (check_av(av, ac) != 0 || (ac != 5 && ac != 6))
		return (0);
	if (init_all(av) != 0)
		return (0);
	launcher();
	destroy_mutex();
}
