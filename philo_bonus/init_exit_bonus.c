/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/02 21:16:54 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_philos(t_program *prog, int *args, int id)
{
	prog->philos[id].id = id + 1;
	prog->philos[id].pid = -1;
	prog->philos[id].meals_eaten = 0;
	prog->philos[id].time_meal = prog->start_time;
	prog->philos[id].num_of_philos = args[0];
	prog->philos[id].time_to_die = args[1];
	prog->philos[id].time_to_eat = args[2];
	prog->philos[id].time_to_sleep = args[3];
	prog->philos[id].num_times_to_eat = args[4];
	prog->philos[id].time_start = prog->start_time;
	prog->philos[id].prog = prog;
}

void	ft_init_program(t_program *prog, int *args)
{
	prog->start_time = get_current_time() + args[0] * 2;
	prog->dead_flag = 0;
	prog->num_of_philos = args[0];
	prog->meal_sem = sem_open("/meal_sem", O_CREAT, 0644, 1);
	prog->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	prog->forks_sem = sem_open("/forks_sem", O_CREAT, 0644,
			prog->num_of_philos);
	prog->full_sem = sem_open("/full_sem", O_CREAT, 0644, 0);
	prog->table_sem = sem_open("/table_sem", O_CREAT, 0644,
			args[0] / 2 + args[0] % 2);
	if (prog->meal_sem == SEM_FAILED || prog->write_sem == SEM_FAILED
		|| prog->forks_sem == SEM_FAILED || prog->full_sem == SEM_FAILED
		|| prog->table_sem == SEM_FAILED)
		ft_finish(prog, RED"Semaphore open error"RESET, 1, EXIT_FAILURE);
	if (sem_unlink("/meal_sem") == -1 || sem_unlink("/write_sem") == -1
		|| sem_unlink("/forks_sem") == -1 || sem_unlink("/full_sem") == -1
		|| sem_unlink("/table_sem") == -1)
		ft_finish(prog, RED"Semaphore unlink error"RESET, 1, EXIT_FAILURE);
}

void	ft_finish(t_program *prog, char *error, int parent, int signal)
{
	int	i;

	i = -1;
	if (parent)
	{
		while (++i < prog->num_of_philos)
			if (prog->philos[i].pid != -1)
				kill(prog->philos[i].pid, SIGKILL);
	}
	if (prog->meal_sem != SEM_FAILED)
		sem_close(prog->meal_sem);
	if (prog->write_sem != SEM_FAILED)
		sem_close(prog->write_sem);
	if (prog->forks_sem != SEM_FAILED)
		sem_close(prog->forks_sem);
	if (prog->full_sem != SEM_FAILED)
		sem_close(prog->full_sem);
	if (prog->table_sem != SEM_FAILED)
		sem_close(prog->table_sem);
	ft_exit(error, signal);
}

void	ft_exit(char *error, int signal)
{
	if (error)
	{
		printf("%s\n", error);
		exit(signal);
	}
	else
		exit(signal);
}
