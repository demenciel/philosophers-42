/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:44:15 by acouture          #+#    #+#             */
/*   Updated: 2023/05/08 17:38:23 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*call_struct(void)
{
	static t_data	data;

	return (&data);
}

void	my_sleep(uint64_t time)
{
	uint64_t	start_time;

	start_time = time_stamp();
	while (((time_stamp() - start_time) < time))
		usleep(50);
}

int	main(int ac, char **av)
{
	if (check_av(av, ac) == 1 || ac < 5)
		return (1);
	else
	{
		if (!init_all(av))
			return (0);
		if (!launch_philo())
			return (0);
	}
}
