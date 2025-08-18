/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/18 19:12:15 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->time_start)
		usleep(50);
	while (!(*(philo->dead)))
	{
		ft_fork(philo);
		ft_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_status(philo, "is thinking");
	}
	return (NULL);
}

void	*ft_fork(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_status(philo, "has taken a fork");
		while (!(*philo->dead))
			ft_usleep(100);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		ft_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		ft_status(philo, "has taken a fork");
	}
	ft_eat(philo);
	return (pthread_mutex_unlock(philo->r_fork),
		pthread_mutex_unlock(philo->l_fork), NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->time_meal = get_current_time();
	ft_status(philo, "is eating");
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	ft_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	if (!(*philo->dead))
		printf ("%zu %d %s\n",
			get_current_time() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}
