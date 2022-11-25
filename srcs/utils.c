/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:21:09 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:21:09 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

long	ft_atoi_p(const char *str)
{
	int		i;
	long	k;

	i = 0;
	k = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		if (str[i + 1] != '\0' && (str[i + 1] < 47 || str[i + 1] > 58))
			return (0);
		k = k * 10 + (str[i] - 48);
		i++;
	}
	return (k);
}

long long unsigned int	ft_current_time(void)
{
	struct timeval			current_time;
	long long unsigned int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = ((current_time.tv_sec * 1000) \
				+ (current_time.tv_usec / 1000));
	return (timestamp);
}

void	ft_milisec_sleep(int milliseconds)
{
	long long unsigned int	starting_value;

	starting_value = ft_current_time();
	while (ft_current_time() < milliseconds + starting_value)
	{
	}
}

long	ft_calculate_timedifference(t_philo *philo)
{
	long	time_diff;

	time_diff = ft_current_time() - philo->table->start_time;
	return (time_diff);
}

void	ft_save_print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&(philo->table->print_mutex));
	printf("%07li Philosopher %li %s.\n", \
			ft_calculate_timedifference (philo), philo->id, action);
	pthread_mutex_unlock(&(philo->table->print_mutex));
}
