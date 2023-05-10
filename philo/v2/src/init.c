/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:34:52 by acouture          #+#    #+#             */
/*   Updated: 2023/05/10 14:41:26 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int init_all(char **av)
{
    init_args(av);
    init_philo();
    if (init_mutex() != 0)
        return (1);
    return (0);
}

void    init_args(char **av)
{
    t_data *data;

    data = call_struct();
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->must_eat = ft_atoi(av[5]);
    else
        data->must_eat = 0;
    data->dead = false;
    data->full = false;
}

void    init_philo()
{
    int i;
    t_philo *philo;
    t_data *data;

    i = 0;
    data = call_struct();
    while (i < data->nb_philo)
    {
        philo = &data->philo[i];
        philo->nb_eat = 0;
        philo->philo_id = (i + 1);
        i++;
    }
}

int init_mutex()
{
    int i;
    t_data *data;

    i = 0;
    data = call_struct();
    while (i < data->nb_philo)
    {
        if (pthread_mutex_init(&data->mutex.fork[i], NULL) != 0)
            return (1);
        i++;
    }
    pthread_mutex_init(&data->mutex.check_death, NULL);
    pthread_mutex_init(&data->mutex.fork_taken, NULL);
    pthread_mutex_init(&data->mutex.eat, NULL);
    pthread_mutex_init(&data->mutex.print, NULL);
    pthread_mutex_init(&data->mutex.sleep, NULL);
    return (0);
}

