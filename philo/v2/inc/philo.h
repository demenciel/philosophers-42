/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:21:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/09 17:37:44 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				nb_eat;
	uint64_t		time_last_meal;

}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	check_death;
	pthread_mutex_t	sleep;
}					t_mutex;

typedef struct s_data
{
	t_mutex			mutex;
	t_philo			philo[200];
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	uint64_t		start_time;
}					t_data;

// MAIN
t_data				*call_struct(void);

// UTILS
int					check_av(char **av);
int					ft_atoi(char *s);
uint64_t			time_stamp(void);
int					print_action(int philo_id, uint64_t stamp, char *action);

// INIT
int					init_all(char **av);
int					init_mutex(void);
void				init_philo(void);
void				init_args(char **av);

// THREADS
void				launcher(void);
void				*routine(void *param);

#endif