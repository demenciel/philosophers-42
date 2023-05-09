/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:20:35 by acouture          #+#    #+#             */
/*   Updated: 2023/05/09 17:20:33 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data *call_struct(void)
{
    static t_data data;

    return (&data);
}

int main(int ac, char **av)
{
    if (ac < 5 || check_av(av) == 1)
        return (0);
    init_all(av);
    launcher();
}