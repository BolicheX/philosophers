/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/18 19:15:59 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* printf ("Num of Philosophers: %d\nTime to die: %d\nTime to eat: %d\n
	Time to sleep: %d\nNum of meals: %d\n", args[0], args[1],
	args[2], args[3], args[4]); */
void	*ft_parse(int *args, char **argv, int argc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isnum(argv[i]))
			ft_exit(1);
		if (ft_atoi(argv[i]) < 0)
			ft_exit(1);
		args[i - 1] = ft_atoi(argv[i]);
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
		pthread_create(&prog->philos[i].thread, NULL,
			&ft_routine, (void *)&prog->philos[i]);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
}

void	ft_finish(t_program *prog)
{
	int	i;

	//pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);
	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int				args[5];
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				i;

	if (argc < 5 || argc > 6)
		return (ft_exit(1));
	ft_parse(args, argv, argc);
	if (args[0] > 200)
		return (ft_exit(1));
	ft_init_program(&program, args);
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
	ft_finish(&program);
	return (ft_exit(0));
}
