/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/03 03:46:51 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitoring(void *arg)
{
	t_program	*prog;

	prog = (t_program *)arg;
	while (get_current_time() < prog->start_time)
		usleep(50);
	while (1)
	{
		if (ft_check_full(prog) || ft_check_dead(prog))
		{
			prog->death = 1;
			pthread_mutex_lock(&prog->meal_lock);
			pthread_mutex_lock(&prog->write_lock);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

/* 		printf("Checking ID: %d at: %ld, last meal:
			%ld, delta: %ld, ttd: %ld\n",
			prog->philos[i].id,
			current_time - prog->philos[i].time_start,
			prog->philos[i].time_meal - prog->philos[i].time_start,
			time_diff,
			prog->philos[i].time_to_die); */
int	ft_check_dead(t_program *prog)
{
	int		i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (get_current_time() - prog->philos[i].time_meal
			> prog->philos[i].time_to_die)
		{
			ft_status(&prog->philos[i], RED"died"RESET);
			pthread_mutex_unlock(&prog->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	return (0);
}

int	ft_check_full(t_program *prog)
{
	int	full_philos;
	int	i;

	i = 0;
	full_philos = 0;
	if (prog->num_times_to_eat == -1)
		return (0);
	while (i < prog->num_of_philos)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (prog->philos[i].meals_eaten >= prog->num_times_to_eat)
			full_philos++;
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	if (full_philos == prog->num_of_philos)
		return (1);
	return (0);
}
