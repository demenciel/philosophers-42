/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:20:35 by acouture          #+#    #+#             */
/*   Updated: 2023/05/17 07:44:18 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
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
			philo->time_last_meal = time_stamp();
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
	if (ac < 5 || check_av(av) == 1)
		return (0);
	init_all(av);
	if (call_struct()->nb_philo == 1)
	{
		print_action(1, 0, PHILO_DEAD);
		return (0);
	}
	launcher();
	destroy_mutex();
}