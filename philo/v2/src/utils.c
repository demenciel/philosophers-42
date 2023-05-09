/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:27:41 by acouture          #+#    #+#             */
/*   Updated: 2023/05/09 17:43:58 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int ft_atoi(char *s)
{
    int res;
    
    res = 0;
    while (*s)
        res = res * 10 + *s++ - '0';
    return (res);
}

int check_av(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] >= '9' && av[i][j] <= '0')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

uint64_t time_stamp()
{
    struct timeval currentTime;
    
    gettimeofday(&currentTime, NULL);
    return ((currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000));
}

int print_action(int philo_id, uint64_t stamp, char *action)
{
    t_data *data;
    uint64_t time_diff;

    data = call_struct();
    time_diff = (stamp - data->start_time);
    pthread_mutex_lock(&data->mutex.print);
    printf("%lld ms : Philo %d %s\n", time_diff, philo_id, action);
    pthread_mutex_unlock(&data->mutex.print);
    return (0);
}
