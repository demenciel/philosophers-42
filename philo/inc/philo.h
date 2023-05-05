/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:45:36 by acouture          #+#    #+#             */
/*   Updated: 2023/05/05 14:20:16 by acouture         ###   ########.fr       */
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
	struct s_data	*data;
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
	int				start_time;
	pthread_mutex_t	fork_access;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	t_philo			philo[200];
	pthread_t		monitor_thread;
}					t_data;

// UTILS ---------------------------------------------------------------------
int					ft_atoi(char *s);
long long			time_stamp(void);
long long			time_to_action(long long end_time);
int					check_av(char **av, int ac);
void				print_action(long long time, int id, char *action);

// MAIN ---------------------------------------------------------------------
t_data				*call_struct(void);

// THREAD CHECK
void				philo_eating(t_philo *philo);
int				check_for_death(void);

// INIT
void				init_all(char **av);
void				init_data(char **av);
void				init_mutex(void);
void				init_philo(void);

#endif