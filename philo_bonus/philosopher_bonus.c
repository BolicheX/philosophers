/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/09 18:21:18 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_born(t_philo *philo)
{
	while (get_current_time() < philo->time_start)
		usleep(50);
	if ((pthread_create(&philo->death_thread, NULL, &ft_check_dead, philo) != 0)
		|| pthread_detach(philo->death_thread) != 0)
		ft_finish(philo->prog, RED"Thread error"RESET, 0, EXIT_FAILURE);
	while (1)
		ft_routine(philo);
}

void	ft_routine(t_philo *philo)
{
	sem_wait(philo->prog->table_sem);
	sem_wait(philo->prog->forks_sem);
	ft_status(philo, CYAN"has taken a fork"RESET);
	sem_wait(philo->prog->forks_sem);
	ft_status(philo, CYAN"has taken a fork"RESET);
	ft_status(philo, GREEN"is eating"RESET);
	sem_wait(philo->prog->meal_sem);
	philo->time_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->prog->meal_sem);
	if (philo->meals_eaten == philo->num_times_to_eat)
		sem_post(philo->prog->full_sem);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->prog->forks_sem);
	sem_post(philo->prog->forks_sem);
	sem_post(philo->prog->table_sem);
	ft_status(philo, BLUE"is sleeping"RESET);
	ft_usleep(philo->time_to_sleep);
	ft_status(philo, YELLOW"is thinking"RESET);
}

void	*ft_check_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->prog->meal_sem);
		if (get_current_time() - philo->time_meal > philo->time_to_die)
		{
			ft_status(philo, RED"died"RESET);
			sem_wait(philo->prog->write_sem);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->prog->meal_sem);
	}
	return (NULL);
}

void	ft_status(t_philo *philo, char *str)
{
	sem_wait(philo->prog->write_sem);
	printf("%zu %d %s\n",
		get_current_time() - philo->time_start, philo->id, str);
	sem_post(philo->prog->write_sem);
}
