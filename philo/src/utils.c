/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:14 by acouture          #+#    #+#             */
/*   Updated: 2023/05/06 15:06:26 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] == 32)
		i++;
	while (s[i] <= '9' && s[i] >= '0')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res);
}

/**

	* @brief Calculate the time between the start of the program and the call to action
 * @param end_time The time stamp of the call to action
 * @return The time elapsed since the start of the program
*/
u_int64_t	time_to_action(uint64_t end_time)
{
	return ((end_time - call_struct()->start_time));
}

/**
 * @brief Check each arguments of the program to look for invalid characters
 * @param av The program's parameters
 * @param ac The numbers of parameters
*/
int	check_av(char **av, int ac)
{
	int	i;
	int	j;

	i = ac - 1;
	j = 0;
	while (i)
	{
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0' || j >= 11)
				return (1);
			j++;
		}
		i--;
	}
	return (0);
}

/**
 * @brief Using gettimeofday(), creates a time stamp
 * @return The time stamp
*/
u_int64_t	time_stamp(void)
{
	struct timeval	currentTime;

	gettimeofday(&currentTime, NULL);
	return ((currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000));
}

/**
 * @brief Depending of the action, prints the time and message of the action
 * @param id The id of the thread doing the action
 * @param action The string to print
*/
void	print_action(int id, char *action)
{
	u_int64_t current_time = time_stamp();
	u_int64_t elapsed_time = time_to_action(current_time);
	
	printf("%lld ms : Philo %d %s\n", elapsed_time, id, action);
}