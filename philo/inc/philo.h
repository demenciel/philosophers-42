/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:45:36 by acouture          #+#    #+#             */
/*   Updated: 2023/05/01 16:25:34 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define PHILO_EATING "is eating"
# define PHILO_SLEEPING "is sleeping"
# define PHILO_THINKING "is thinking"
# define PHILO_DEAD "died"

typedef struct s_philo
{
	pthread_t		thread_id;
	struct s_data	*data;
	int				philo_id;
	int				fork_id;
	int				status;
	int				nb_time_eat;
	int				time_last_meal;
}					t_philo;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_philo;
	int				start_time;
	pthread_mutex_t	fork[200];
	t_philo			philo[200];

}					t_data;

// UTILS ---------------------------------------------------------------------
t_data				*call_struct(void);
long long			time_stamp(void);
int					init_data(char **av);
int					ft_atoi(char *s);
int					check_av(char **av, int ac);
int					time_to_action(long long end_time);

#endif