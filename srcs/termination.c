/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:20:47 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:20:47 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	*ft_meal_termination(t_philo *philos)
{
	int		k;
	int		*exit_var;

	exit_var = malloc (sizeof(int));
	pthread_mutex_lock(&(philos->table->print_mutex));
	pthread_mutex_lock(&(philos->table->time_mutex));
	printf("%07li Desired number of started meals reached.\n", \
			ft_calculate_timedifference (philos));
	pthread_mutex_unlock(&(philos->table->time_mutex));
	k = 0;
	while (k < philos->table->num_philos)
	{
		if ((philos[k].thread) != 0)
		{
			pthread_mutex_lock(&(philos[k].termination_mutex));
			philos[k].termination_flag = 1;
			pthread_mutex_unlock(&(philos[k].termination_mutex));
		}
		k++;
	}
	pthread_mutex_unlock(&(philos->table->print_mutex));
	*exit_var = 2;
	return (exit_var);
}

int	*ft_death_termination(t_philo *philos, int i)
{
	int		j;
	int		*exit_var;

	exit_var = malloc (sizeof(int));
	pthread_mutex_lock(&(philos->table->print_mutex));
	pthread_mutex_lock(&(philos->table->time_mutex));
	printf("%07li Philosopher %ld died.\n", \
		ft_calculate_timedifference (philos), philos[i].id);
	pthread_mutex_unlock(&(philos->table->time_mutex));
	j = 0;
	while (j < philos->table->num_philos)
	{
		if ((philos[j].thread) != 0)
		{
			pthread_mutex_lock(&(philos[j].termination_mutex));
			philos[j].termination_flag = 1;
			pthread_mutex_unlock(&(philos[j].termination_mutex));
		}
		j++;
	}
	pthread_mutex_unlock(&(philos->table->print_mutex));
	*exit_var = 1;
	return (exit_var);
}

void	*ft_termination_check(void *arg)
{
	t_philo	*philos;
	int		i;
	int		t_last_meal;
	long	meals_all;

	philos = (t_philo *)arg;
	meals_all = 9999999999;
	while (1 && meals_all != 0)
	{
		i = 0;
		meals_all = 0;
		while (i < philos->table->num_philos)
		{
			pthread_mutex_lock(&(philos[i].meals_mutex));
			meals_all += philos[i].meals;
			pthread_mutex_unlock(&(philos[i].meals_mutex));
			pthread_mutex_lock(&(philos->table->eat_mutex));
			t_last_meal = (int)(ft_current_time() - (philos[i].eat_timestamp));
			pthread_mutex_unlock(&(philos->table->eat_mutex));
			if (t_last_meal >= philos->table->time_to_die)
				return ((void *) ft_death_termination(philos, i));
		i++;
		}
	}
	return ((void *) ft_meal_termination(philos));
}

void	ft_mutex_destroy(t_philo *philos)
{
	int	j;

	j = 0;
	while (j < philos->table->num_philos)
	{
		if (pthread_mutex_destroy(&(philos->table->forks[j].fork_mutex)) != 0)
			perror("Failed to destroy fork mutex");
		if (pthread_mutex_destroy(&(philos[j].termination_mutex)) != 0)
			perror("Failed to destroy termination mutex");
		if (pthread_mutex_destroy(&(philos[j].meals_mutex)) != 0)
			perror("Failed to destroy meals mutex");
		j++;
	}
	if (pthread_mutex_destroy(&(philos->table->eat_mutex)) != 0)
		perror("Failed to destroy eat mutex");
	if (pthread_mutex_destroy(&(philos->table->time_mutex)) != 0)
		perror("Failed to destroy time mutex");
	if (pthread_mutex_destroy(&(philos->table->print_mutex)) != 0)
		perror("Failed to destroy print mutex");
}

void	ft_res_release(t_philo *philos, int *ret)
{
	int	j;

	j = 0;
	while (j < philos->table->num_philos)
	{
		if (pthread_join((philos[j].thread), NULL) != 0)
			perror("Failed to join thread");
		j++;
	}
	ft_mutex_destroy(philos);
	free(ret);
	free(philos->table->forks);
	free(philos->table);
	free(philos);
}
