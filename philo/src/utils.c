/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:27:41 by acouture          #+#    #+#             */
/*   Updated: 2023/05/24 13:20:05 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Converts an array to an integer
*/
int	ft_atoi(char *s)
{
	int	res;

	res = 0;
	while (*s)
		res = res * 10 + *s++ - '0';
	return (res);
}

/**
 * Check if each of the inputs are only positive ints
*/
int	check_av(char **av, int ac)
{
	int	j;
	int	i;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Custom sleep function
*/
void	my_sleep(uint64_t time)
{
	uint64_t	goal;

	goal = time_stamp() + time;
	while (1)
	{
		if (time_stamp() >= goal)
			return ;
		usleep(50);
	}
}

/**
 * Using gettimeofday, creates a time stamp
*/
uint64_t	time_stamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/**
 * Prints the thread id,
	the time since the program as started and the message wanted to be printed
*/
int	print_action(int philo_id, uint64_t stamp, char *action)
{
	t_data		*data;
	uint64_t	time_diff;
	bool		dead;

	data = call_struct();
	pthread_mutex_lock(&data->mutex.print);
	time_diff = stamp - data->start_time;
	pthread_mutex_lock(&data->mutex.change_state);
	dead = data->dead;
	pthread_mutex_unlock(&data->mutex.change_state);
	if (dead == false)
		printf("%lld ms Philo %d %s\n", time_diff, philo_id, action);
	pthread_mutex_unlock(&data->mutex.print);
	return (0);
}
