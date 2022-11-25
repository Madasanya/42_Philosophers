/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 03:04:33 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/08 03:04:33 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	long			last_philo;
}	t_fork;

typedef struct s_table
{
	long long unsigned int	start_time;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_to_die;
	long					num_philos;
	t_fork					*forks;
	pthread_mutex_t			eat_mutex;
	pthread_mutex_t			time_mutex;
	pthread_mutex_t			print_mutex;

}	t_table;

typedef struct s_philo
{
	pthread_t				thread;
	long					id;
	long					meals;
	long long unsigned int	eat_timestamp;
	t_table					*table;
	int						termination_flag;
	pthread_mutex_t			termination_mutex;
	pthread_mutex_t			meals_mutex;
	long					frst;
	long					scnd;
}	t_philo;

/* utils.c */
long					ft_atoi_p(const char *str);
long long unsigned int	ft_current_time(void);
void					ft_milisec_sleep(int milliseconds);
long					ft_calculate_timedifference(t_philo *philo);
void					ft_save_print(t_philo *philo, char *action);

/* main_and_input_checks.c */
int						ft_argc_checks(int argc);
int						ft_argv_checks(char **argv);
int						ft_input_checks(int argc, char **argv);
int						main(int argc, char **argv);

/* initalizations.c */
void					ft_fork_assignment(t_philo *philo);
void					ft_philos_init(int argc, char **argv, \
						t_philo *philos, t_table *table);
void					ft_forks_init(int num_philos, t_fork *forks);
void					ft_table_init(t_table **table, t_fork *forks, \
						char **argv, int n_p);
void					ft_init(t_philo **philos, int argc, char **argv);

/* philo_life.c */
void					ft_eating(t_philo *philo);
void					ft_sleeping(t_philo *philo);
void					*ft_philo_life(void *philo_args);

/* philo_life_helper.c */
void					ft_save_termination_flag(t_philo *philo, \
						int *termination);
void					ft_save_val_assign(t_philo *philo, long *last_frst, \
						long *last_scnd, int *termination);
void					ft_save_philos(t_philo *philo, int *termination);
void					ft_save_philo(t_philo *philo);
void					*ft_free_help_vars(long *last_frst, long *last_scnd, \
						int *termination);

/* termination.c */
int						*ft_meal_termination(t_philo *philos);
int						*ft_death_termination(t_philo *philos, int i);
void					*ft_termination_check(void *arg);
void					ft_res_release(t_philo *philos, int *ret);
void					ft_mutex_destroy(t_philo *philos);

/* thread_creation.c */
int						ft_thread_creation(t_philo *philos, int i);
int						ft_even_odd_calc(int num_philos, int batch);

#endif