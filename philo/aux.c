/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:06:53 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/11 17:52:54 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnum(char *s)
{
	if (*s == '\0')
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	if (*s >= '0' && *s <= '9')
	{
		while (*s)
		{
			if (!(*s >= '0' && *s <= '9'))
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10UL + ((unsigned long)str[i] - '0');
		i++;
	}
	return ((int)res * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}