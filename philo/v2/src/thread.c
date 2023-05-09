/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:03 by acouture          #+#    #+#             */
/*   Updated: 2023/05/09 17:40:38 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    *routine(void *param)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)param;
    data = call_struct();

    pthread_mutex_lock(data->mutex.fork);
    for (int i = 0; i < 10; i++) {
        printf("Philo %d - %d\n", philo->philo_id, i);
    }
    print_action(philo->philo_id, time_stamp(), "DONE");
    pthread_mutex_unlock(data->mutex.fork);
    return (NULL);
}

void    wait_thread()
{
    t_philo *philo;
    t_data *data;
    int i;

    i = 0;
    data = call_struct();
    while (i < data->nb_philo)
    {
        philo = &data->philo[i];
        pthread_join(philo->thread_id, NULL);
        i++;
    }
}

void    launcher(void)
{
    int i;
    t_data *data;
    t_philo *philo;

    i = 0;
    data = call_struct();
    data->start_time = time_stamp();
    printf("%lld\n", data->start_time);
    while (i < data->nb_philo)
    {
        philo = &data->philo[i];
        philo->time_last_meal = time_stamp();
        pthread_create(&philo->thread_id, NULL, routine, philo);
        i++;
    }
    wait_thread();
}