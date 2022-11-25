/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:20:57 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:20:57 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	ft_thread_creation(t_philo *philos, int i)
{
	while (i < philos->table->num_philos)
	{
		if (pthread_create(&(philos[i].thread), NULL, \
			&ft_philo_life, &(philos[i])) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		i = i + 2;
	}
	return (0);
}

int	ft_even_odd_calc(int num_philos, int batch)
{
	if (batch == 1)
	{
		if ((num_philos % 2) == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((num_philos % 2) == 0)
			return (0);
		else
			return (1);
	}
}
