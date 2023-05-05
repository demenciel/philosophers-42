/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:01:47 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 16:35:47 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    *routine(void *void_philo)
{
    t_philo *philo;

    philo = (t_philo *)void_philo;
    if(take_forks(philo->philo_id) != 0)
        return (NULL);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }
    // philo_eating(philo);
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

int launch_philo()
{
    int i = 0;
    t_philo *philo;

    call_struct()->start_time = time_stamp();
    init_philo();
    while (i < call_struct()->nb_of_philo)
    {
        philo = &call_struct()->philo[i];
        if (pthread_create(&philo->thread_id, NULL, routine, philo) != 0)
            return (EXIT_FAILURE);
        i++;
    }
    if (wait_thread() != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}