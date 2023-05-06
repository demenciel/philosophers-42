/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/06 15:30:19 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    *routine(void *void_philo)
{
    t_philo *philo;
    t_data *data;

    data = call_struct();
    philo = (t_philo *)void_philo;
    if (philo->philo_id % 2 == 0)
        my_sleep(data->time_to_eat);
    philo = (t_philo *)void_philo;
    while (!(data->dead) && ((philo[data->nb_of_philo].nb_time_eat) != data->must_eat))
    {
        philo_forks(philo);
        my_sleep(data->time_to_sleep);
        print_action(philo->philo_id, PHILO_SLEEPING);
        my_sleep(data->time_to_sleep);
        print_action(philo->philo_id, PHILO_THINKING);
    }
    return (NULL);
}

int wait_thread()
{
    int i = 0;

    while (i < call_struct()->nb_of_philo)
    {
        if (pthread_join(call_struct()->philo[i].thread_id, NULL) != 0)
            return (printf("Error : %d\n", EXIT_FAILURE));
        i++;
    }
    return (EXIT_SUCCESS);
}

int check_death()
{
    int i;
    int nb_philo;
    int time_to_die;
    int time_check;
    t_philo *philo;

    i = 0;
    nb_philo = call_struct()->nb_of_philo;
    time_to_die = call_struct()->time_to_die;
    while (1)
    {
        while (i < nb_philo)
        {
            philo = &call_struct()->philo[i]; 
            time_check = time_stamp() - philo->time_last_meal;
            if (time_check >= time_to_die)
            {
                print_action(philo->philo_id, PHILO_DEAD);
                call_struct()->dead = true;
                return (EXIT_FAILURE);
            }
            i++;
        }
        i = 0;
    }
    return (EXIT_SUCCESS);
}

int launch_philo()
{
    int i = 0;
    t_philo *philo;

    init_philo();
    init_mutex();
    call_struct()->start_time = time_stamp();
    while (i < call_struct()->nb_of_philo)
    {
        philo = &call_struct()->philo[i];
        if (pthread_create(&philo->thread_id, NULL, routine, philo) != 0)
            return (EXIT_FAILURE);
        i++;
    }
    if (check_death() != 0)
        return (EXIT_FAILURE);
    if (wait_thread() != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}