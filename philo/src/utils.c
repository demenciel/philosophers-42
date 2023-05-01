/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:14 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 15:38:45 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int ft_atoi(char *s)
{
    int res;

    while (*s <= 32)
        s++;
    while (*s <= '9' && *s >= '0')
        res = res * 10 + *s++ - '0';
    return (res);
}

int	time_to_action(long long end_time)
{
	return (end_time - call_struct()->start_time);
}

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

long long	time_stamp(void)
{
    struct timeval  currentTime;
    
    gettimeofday(&currentTime, NULL);
	return ((currentTime.tv_sec) + (currentTime.tv_usec));
}