/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:17 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 16:33:32 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int take_forks(int id)
{
    int nb_philo;
    pthread_mutex_t *fork1;
    pthread_mutex_t *fork2;

    nb_philo = call_struct()->nb_of_philo;
    fork1 = &call_struct()->fork[id];
    fork2 = &call_struct()->fork[(id + 1) % nb_philo];
    if (pthread_mutex_lock(fork1) != 0)
    {
        printf("ERROR1\n");
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_lock(fork2) != 0)
    {
        printf("ERROR2\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

void    philo_eating(t_philo *philo)
{
    (void)philo;
}