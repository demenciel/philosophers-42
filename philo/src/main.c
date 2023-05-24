/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:20:35 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 13:26:21 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
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
 * To avoid data races,
	initalize by time stamping the last meal of each philo 
    before starting the threads
*/
void	stamp_last_meal(void)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	data = call_struct();
	if (data->last_meal_stamped == false)
	{
		while (i < data->nb_philo)
		{
			philo = &data->philo[i];
			pthread_mutex_lock(&data->mutex.last_meal);
			philo->time_last_meal = time_stamp();
			pthread_mutex_unlock(&data->mutex.last_meal);
			i++;
		}
		data->last_meal_stamped = true;
	}
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
	if (call_struct()->nb_philo == 1)
	{
		print_action(1, 0, PHILO_DEAD);
		destroy_mutex();
		return (0);
	}
	launcher();
	destroy_mutex();
}
