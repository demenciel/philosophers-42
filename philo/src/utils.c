/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:14 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 16:54:33 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int ft_atoi(char *s)
{
    int i;
    int res;

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
int	time_to_action(long long end_time)
{
	return (end_time - call_struct()->start_time);
}

/**
 * @brief Check each arguments of the program to look for invalid characters
 * @param av The program's parameters
 * @param ac The numbers of parameters
*/
int check_av(char **av, int ac)
{
    int i;
    int j;
    
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
long long	time_stamp(void)
{
    struct timeval  currentTime;
    
    gettimeofday(&currentTime, NULL);
	return ((currentTime.tv_sec) + (currentTime.tv_usec));
}