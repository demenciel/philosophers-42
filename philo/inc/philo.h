/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:45:36 by acouture          #+#    #+#             */
/*   Updated: 2023/05/06 15:19:57 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
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
	bool			is_dead;
	int				philo_id;
	int				nb_time_eat;
	int				time_last_meal;
}					t_philo;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_philo;
	int				must_eat;
	uint64_t		start_time;
	bool			dead;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	t_philo			philo[200];
}					t_data;

// UTILS ---------------------------------------------------------------------
int					ft_atoi(char *s);
u_int64_t			time_stamp(void);
u_int64_t			time_to_action(uint64_t end_time);
int					check_av(char **av, int ac);
void				print_action(int id, char *action);

// MAIN ---------------------------------------------------------------------
t_data				*call_struct(void);
void				my_sleep(uint64_t time);

// ACTIONS
void				philo_forks(t_philo *philo);
void				philo_eating(t_philo *philo);

// THREADS
int					launch_philo(void);
void				*routine(void *void_philo);

// INIT
int					init_all(char **av);
int					init_args(char **av);
void				init_philo(void);
void				init_mutex(void);

#endif