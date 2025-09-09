/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/09 17:58:19 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_parse(int *args, char **argv, int argc)
{
	int		i;
	long	num;

	i = 1;
	if (argc < 5 || argc > 6)
		ft_exit(RED"Invalid number of arguments"RESET, 1);
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (!ft_isnum(argv[i]))
			ft_exit(RED"Invalid argument"RESET, 1);
		if (num < 0)
			ft_exit(RED"Invalid argument"RESET, 1);
		if (i == 1 && num > PHILO_MAX_COUNT)
			ft_exit(RED"Maximum number of philosophers exceeded"RESET, 1);
		args[i - 1] = num;
		i++;
	}
	if (argc == 5)
		args[4] = -1;
	return (NULL);
}

void	ft_thread(t_program *prog)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	pthread_create(&monitor, NULL, &ft_monitoring, (void *)prog);
	while (i < prog->num_of_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL,
				&ft_routine, (void *)&prog->philos[i]) != 0)
			ft_destroy_mutex(prog, RED"Thread error"RESET, EXIT_FAILURE);
		/*if (pthread_detach(prog->philos[i].thread) != 0)
			ft_destroy_mutex(prog, RED"Thread error"RESET, EXIT_FAILURE);*/
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		ft_destroy_mutex(prog, RED"Monitor Thread error"RESET, EXIT_FAILURE);
	i = 0;
	while (i < prog->num_of_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			ft_destroy_mutex(prog, RED"Philosopher Thread error"RESET, EXIT_FAILURE);
		i++;
	}
	return ;
}

void	ft_destroy_mutex(t_program *prog, char *error, int signal)
{
	int	i;

	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);
	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	ft_exit(error, signal);
}

int	main(int argc, char **argv)
{
	int				args[5];
	t_program		program;
	t_philo			philos[PHILO_MAX_COUNT];
	pthread_mutex_t	forks[PHILO_MAX_COUNT];
	int				i;

	ft_parse(args, argv, argc);
	ft_init_program(&program, args);
	if (program.num_times_to_eat == 0)
		exit(EXIT_SUCCESS);
	program.philos = philos;
	program.forks = forks;
	i = 0;
	while (i < program.num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		ft_init_philos(&program, args, i);
		i++;
	}
	ft_thread(&program);
	ft_destroy_mutex(&program, NULL, 0);
	return (0);
}
