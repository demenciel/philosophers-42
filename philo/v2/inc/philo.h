/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:21:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/10 15:34:44 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
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
	pthread_t		death_thread;
	int				philo_id;
	int				nb_eat;
	uint64_t		time_last_meal;

}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	change_state;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	check_death;
}					t_mutex;

typedef struct s_data
{
	t_mutex			mutex;
	t_philo			philo[200];
	bool			dead;
	bool 			full;
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
void				my_sleep(uint64_t time);
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
void				wait_thread(void);
void				*routine(void *param);
int					check_death(void);
int					check_full(void);

// ACTIONS
void				philo_fork(t_philo *philo);
void				philo_sleeping(t_philo *philo);
#endif