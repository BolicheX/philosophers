/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/03 00:40:16 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_exec(t_program *prog)
{
	int			i;
	pid_t		pid;
	pthread_t	full_thread;

	i = -1;
	if (prog->philos[0].num_times_to_eat > 0)
	{
		if (pthread_create(&full_thread, NULL, &ft_check_full, prog) == -1)
			ft_finish(prog, RED"Thread creation error"RESET, 1, EXIT_FAILURE);
		if (pthread_detach(full_thread) == -1)
			ft_finish(prog, RED"Thread detach error"RESET, 1, EXIT_FAILURE);
	}
	while (++i < prog->num_of_philos)
	{
		pid = fork();
		if (pid < 0)
			ft_finish(prog, RED"Fork error"RESET, 1, EXIT_FAILURE);
		prog->philos[i].pid = pid;
		if (pid == 0)
			ft_philo_born(&prog->philos[i]);
	}
	waitpid(-1, NULL, 0);
	ft_finish(prog, NULL, 1, EXIT_SUCCESS);
}

void	*ft_check_full(void *arg)
{
	t_program	*prog;
	int			full;

	prog = (t_program *)arg;
	full = 0;
	while (get_current_time() < prog->start_time)
		usleep(50);
	while (1)
	{
		sem_wait(prog->full_sem);
		full++;
		if (full >= prog->num_of_philos)
		{
			sem_wait(prog->write_sem);
			ft_finish(prog, NULL, 1, EXIT_SUCCESS);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				args[5];
	t_program		program;
	t_philo			philos[PHILO_MAX_COUNT];
	int				i;

	ft_parse(args, argv, argc);
	ft_init_program(&program, args);
	program.philos = philos;
	i = 0;
	while (i < program.num_of_philos)
		ft_init_philos(&program, args, i++);
	ft_exec(&program);
	return (0);
}
