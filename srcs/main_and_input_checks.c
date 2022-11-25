/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_and_input_checks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:19:37 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/30 16:19:37 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	ft_argc_checks(int argc)
{
	if ((argc != 5) && (argc != 6))
	{
		printf("Wrong input: Incorrect number of arguments!\n");
		return (1);
	}
	return (0);
}

int	ft_argv_checks(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi_p(argv[i]) == 0)
		{
			printf("Wrong input: Arguments are invalid!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_input_checks(int argc, char **argv)
{
	if ((ft_argv_checks(argv) == 1) || (ft_argc_checks(argc) == 1))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_philo		*philos;
	pthread_t	termination_thread;
	int			*ret;

	if (ft_input_checks(argc, argv) == 1)
		return (1);
	ret = NULL;
	philos = NULL;
	ft_init(&philos, argc, argv);
	philos->table->start_time = ft_current_time();
	pthread_create(&termination_thread, NULL, \
					&ft_termination_check, philos);
	i = ft_even_odd_calc(philos->table->num_philos, 1);
	if (ft_thread_creation(philos, i) != 0)
		return (1);
	ft_milisec_sleep(5);
	i = ft_even_odd_calc(philos->table->num_philos, 2);
	if (ft_thread_creation(philos, i) != 0)
		return (1);
	if (pthread_join(termination_thread, (void **) &ret) != 0)
		perror("Failed to close thread");
	if (*ret == 1 || *ret == 2)
		ft_res_release(philos, ret);
	return (0);
}
