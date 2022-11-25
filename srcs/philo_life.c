/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:20:08 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:20:08 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_eating(t_philo *philo)
{
	int	termination;

	pthread_mutex_lock(&(philo->termination_mutex));
	termination = philo->termination_flag;
	pthread_mutex_unlock(&(philo->termination_mutex));
	if (termination == 0)
	{
		pthread_mutex_lock(&(philo->table->eat_mutex));
		pthread_mutex_lock(&(philo->table->print_mutex));
		philo->eat_timestamp = ft_current_time();
		printf("%07li Philosopher %ld is eating.\n", \
				ft_calculate_timedifference (philo), philo->id);
		pthread_mutex_unlock(&(philo->table->print_mutex));
		pthread_mutex_unlock(&(philo->table->eat_mutex));
		if (philo->meals > 0)
		{
			pthread_mutex_lock(&(philo->meals_mutex));
			philo->meals--;
			pthread_mutex_unlock(&(philo->meals_mutex));
		}
		ft_milisec_sleep(philo->table->time_to_eat);
	}
}

void	ft_sleeping(t_philo *philo)
{
	int	termination;

	pthread_mutex_lock(&(philo->termination_mutex));
	termination = philo->termination_flag;
	pthread_mutex_unlock(&(philo->termination_mutex));
	if (termination == 0)
	{
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("%07li Philosopher %ld is sleeping.\n", \
				ft_calculate_timedifference (philo), philo->id);
		pthread_mutex_unlock(&(philo->table->print_mutex));
		ft_milisec_sleep(philo->table->time_to_sleep);
	}
}

void	*ft_philo_life(void *philo_args)
{
	t_philo		*philo;
	long		*last_frst;
	long		*last_scnd;
	int			*term;

	philo = (t_philo *)philo_args;
	last_frst = malloc(sizeof(long) * 1);
	last_scnd = malloc(sizeof(long) * 1);
	term = malloc(sizeof(int) * 1);
	ft_save_termination_flag(philo, term);
	while (1 && *term == 0)
	{
		ft_save_val_assign (philo, last_frst, last_scnd, term);
		if (*last_frst != philo->id && *last_scnd != philo->id && *term == 0)
		{
			ft_save_philos(philo, term);
			if (philo->frst == philo->scnd)
			{
				ft_save_philo(philo);
				return (ft_free_help_vars(last_frst, last_scnd, term));
			}
		}
	}
	return (ft_free_help_vars(last_frst, last_scnd, term));
}
