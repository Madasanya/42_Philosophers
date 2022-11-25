/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inititalizations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:58:40 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 15:58:40 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_fork_assignment(t_philo *philo)
{
	if ((philo->id - 1) < ((int)((philo->id) % (philo->table->num_philos))))
	{
		philo->frst = philo->id - 1;
		philo->scnd = (int)((philo->id) % (philo->table->num_philos));
	}
	else
	{
		philo->frst = (int)((philo->id) % (philo->table->num_philos));
		philo->scnd = philo->id - 1;
	}
}

void	ft_philos_init(int argc, char **argv, t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < (table->num_philos))
	{
		philos[i].id = i + 1;
		philos[i].termination_flag = 0;
		if (argc == 6)
			philos[i].meals = ft_atoi_p(argv[5]);
		else
			philos[i].meals = 999999999;
		philos[i].table = table;
		philos[i].eat_timestamp = ft_current_time();
		pthread_mutex_init(&(philos[i].termination_mutex), NULL);
		pthread_mutex_init(&(philos[i].meals_mutex), NULL);
		ft_fork_assignment(&(philos[i]));
		i++;
	}
}

void	ft_forks_init(int num_philos, t_fork *forks)
{
	int		i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&(forks[i].fork_mutex), NULL);
		pthread_mutex_lock(&(forks[i].fork_mutex));
		forks[i].last_philo = 0;
		pthread_mutex_unlock(&(forks[i].fork_mutex));
		i++;
	}
}

void	ft_table_init(t_table **table, t_fork *forks, char **argv, int n_p)
{
	(*table)->num_philos = n_p;
	(*table)->forks = forks;
	(*table)->time_to_die = ft_atoi_p(argv[2]);
	(*table)->time_to_eat = ft_atoi_p(argv[3]);
	(*table)->time_to_sleep = ft_atoi_p(argv[4]);
	(*table)->start_time = 0;
	pthread_mutex_init(&((*table)->eat_mutex), NULL);
	pthread_mutex_init(&((*table)->time_mutex), NULL);
	pthread_mutex_init(&((*table)->print_mutex), NULL);
}

void	ft_init(t_philo **philos, int argc, char **argv)
{
	long	num_philos;
	t_table	*table;
	t_fork	*forks;

	num_philos = ft_atoi_p(argv[1]);
	table = malloc(sizeof(t_table) * 1);
	forks = malloc(sizeof(t_fork) * num_philos);
	*philos = malloc(sizeof(t_philo) * num_philos);
	ft_forks_init(num_philos, forks);
	ft_table_init(&table, forks, argv, num_philos);
	ft_philos_init(argc, argv, *philos, table);
}
