/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:19:53 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:19:53 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_save_termination_flag(t_philo *philo, int *termination)
{
	pthread_mutex_lock(&(philo->termination_mutex));
	*termination = philo->termination_flag;
	pthread_mutex_unlock(&(philo->termination_mutex));
}

void	ft_save_val_assign(t_philo *philo, long *last_frst, long *last_scnd, \
		int *termination)
{
	pthread_mutex_lock(&(philo->table->forks[philo->frst].fork_mutex));
	*last_frst = philo->table->forks[philo->frst].last_philo;
	pthread_mutex_unlock(&(philo->table->forks[philo->frst].fork_mutex));
	pthread_mutex_lock(&(philo->table->forks[philo->scnd].fork_mutex));
	*last_scnd = philo->table->forks[philo->scnd].last_philo;
	pthread_mutex_unlock(&(philo->table->forks[philo->scnd].fork_mutex));
	pthread_mutex_lock(&(philo->termination_mutex));
	*termination = philo->termination_flag;
	pthread_mutex_unlock(&(philo->termination_mutex));
}

void	ft_save_philos(t_philo *philo, int *termination)
{
	pthread_mutex_lock(&(philo->table->forks[philo->frst].fork_mutex));
	ft_save_print(philo, "has taken a fork");
	if (philo->frst != philo->scnd)
	{
		pthread_mutex_lock(&(philo->table->forks[philo->scnd].fork_mutex));
		ft_save_print(philo, "has taken a fork");
		ft_eating(philo);
		philo->table->forks[philo->frst].last_philo = philo->id;
		philo->table->forks[philo->scnd].last_philo = philo->id;
		pthread_mutex_unlock(&(philo->table->forks[philo->scnd].fork_mutex));
		pthread_mutex_unlock(&(philo->table->forks[philo->frst].fork_mutex));
		ft_sleeping(philo);
		pthread_mutex_lock(&(philo->termination_mutex));
		*termination = philo->termination_flag;
		pthread_mutex_unlock(&(philo->termination_mutex));
		if (*termination == 0)
			ft_save_print(philo, "is thinking");
	}
}

void	ft_save_philo(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->table->forks[philo->frst].fork_mutex));
	pthread_mutex_lock(&(philo->termination_mutex));
	philo->termination_flag = 1;
	pthread_mutex_unlock(&(philo->termination_mutex));
}

void	*ft_free_help_vars(long *last_frst, long *last_scnd, int *termination)
{
	free(last_frst);
	free(last_scnd);
	free(termination);
	return ((void *) NULL);
}
