/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/06 13:42:30 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    *routine(void *void_philo)
{
    t_philo *philo;

    if (call_struct()->start_time == 0)
        call_struct()->start_time = time_stamp();
    philo = (t_philo *)void_philo;
    philo_forks(philo);
    
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

    i = 0;
    while ()
}

int launch_philo()
{
    int i = 0;
    t_philo *philo;

    init_philo();
    init_mutex();
    while (i < call_struct()->nb_of_philo)
    {
        philo = &call_struct()->philo[i];
        if (pthread_create(&philo->thread_id, NULL, routine, philo) != 0)
            return (EXIT_FAILURE);
        i++;
    }
    if (wait_thread() != 0)
        return (EXIT_FAILURE);
    if (check_death() != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}