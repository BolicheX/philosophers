/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/03 18:40:31 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->time_start)
		usleep(50);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 10);
	while (1)
	{
		ft_eat(philo);
		ft_status(philo, BLUE"is sleeping"RESET);
		ft_usleep(philo->time_to_sleep);
		ft_status(philo, YELLOW"is thinking"RESET);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_status(philo, CYAN"has taken a fork"RESET);
	pthread_mutex_lock(philo->l_fork);
	ft_status(philo, CYAN"has taken a fork"RESET);
	pthread_mutex_lock(philo->meal_lock);
	philo->time_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_status(philo, GREEN"is eating"RESET);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_status(t_philo *philo, char *str)
{
	if (*philo->death)
		return ;
	pthread_mutex_lock(philo->write_lock);
	printf ("%zu %d %s\n",
		get_current_time() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}
