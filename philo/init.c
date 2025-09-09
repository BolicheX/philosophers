/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/09 18:46:43 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_program *prog, int *args, int id)
{
	prog->philos[id].id = id + 1;
	prog->philos[id].meals_eaten = 0;
	prog->philos[id].time_meal = prog->start_time;
	prog->philos[id].num_of_philos = args[0];
	prog->philos[id].time_to_die = prog->time_to_die;
	prog->philos[id].time_to_eat = args[2];
	prog->philos[id].time_to_sleep = args[3];
	prog->philos[id].num_times_to_eat = args[4];
	prog->philos[id].time_start = prog->start_time;
	if (id % 2 == 0)
	{
		prog->philos[id].r_fork = &prog->forks[id];
		if (id == 0)
			prog->philos[id].l_fork = &prog->forks[args[0] - 1];
		else
			prog->philos[id].l_fork = &prog->forks[id - 1];
	}
	else
	{
		prog->philos[id].r_fork = &prog->forks[id -1];
		prog->philos[id].l_fork = &prog->forks[id];
	}
	prog->philos[id].write_lock = &prog->write_lock;
	prog->philos[id].meal_lock = &prog->meal_lock;
	prog->philos[id].death = &prog->death;
}

void	ft_init_program(t_program *prog, int *args)
{
	size_t	start;

	start = get_current_time() + args[0] * 5;
	prog->start_time = start;
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->num_of_philos = args[0];
	prog->num_times_to_eat = args[4];
	prog->time_to_die = args[1];
	prog->death = 0;
}
