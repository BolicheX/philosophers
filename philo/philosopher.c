/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/09 18:47:09 by jose-jim         ###   ########.fr       */
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
		if (ft_eat(philo))
			return (NULL);
		if (ft_status(philo, BLUE"is sleeping"RESET))
			return (NULL);
		ft_usleep(philo->time_to_sleep);
		if (ft_status(philo, YELLOW"is thinking"RESET))
			return (NULL);
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	int	dead;
	
	pthread_mutex_lock(philo->r_fork);
	dead = ft_status(philo, CYAN"has taken a fork"RESET);
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	dead = ft_status(philo, CYAN"has taken a fork"RESET);
	pthread_mutex_lock(philo->meal_lock);
	philo->time_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	dead = ft_status(philo, GREEN"is eating"RESET);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (dead);
}

int	ft_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	if (*philo->death)
	{	
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	printf ("%zu %d %s\n",
		get_current_time() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}
