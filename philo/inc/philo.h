/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:21:21 by acouture          #+#    #+#             */
/*   Updated: 2023/05/27 09:04:34 by acouture         ###   ########.fr       */
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
	int				philo_id;
	int				nb_eat;
	int				l_fork;
	int				r_fork;
	uint64_t		time_last_meal;

}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	change_state;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	print;
}					t_mutex;

typedef struct s_data
{
	t_mutex			mutex;
	t_philo			philo[200];
	bool			dead;
	bool			last_meal_stamped;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				total_eaten;
	uint64_t		start_time;
}					t_data;

// MAIN
t_data				*call_struct(void);
void				destroy_mutex(void);
int					check_av_values(void);
void				destroy_mutex(void);

// UTILS
int					print_action(int philo_id, uint64_t stamp, char *action);
uint64_t			time_stamp(void);
void				my_sleep(uint64_t time);
int					check_av(char **av, int ac);
int					ft_atoi(char *s);

// INIT
int					init_all(char **av);
void				init_args(char **av);
void				create_philos(void);
void				fill_philo_struct(t_data *data, int i, int j);
int					init_mutex(void);

// THREADS
void				launcher(void);
void				*routine(void *void_philo);
void				wait_thread(void);

// ACTIONS
int					philo_eating(t_philo *philo);

// CHECKERS
int					check_full(void);
int					check_death(void);
#endif
