/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:32:35 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/13 20:09:02 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_exit(int error)
{
	if (error)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}

void	*ft_parse(int *args, char **argv, int argc)
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if (!ft_isnum(argv[i]))
			ft_exit(1);
		if (ft_atoi(argv[i]) <= 0)
			ft_exit(1);
		args[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (argc == 5)
		args[4] = -1;
	else
		args[4] = ft_atoi(argv[5]);
	printf ("Num of Philosophers: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nNum of meals: %d\n", args[0], args[1], args[2], args[3], args[4]);
	return(NULL);
}

void	ft_init_philos(t_program *prog, int *args, int id)
{
	prog->philos[id].id = id + 1;
	prog->philos[id].eating = 0;
	prog->philos[id].meals_eaten = 0;
	prog->philos[id].time_meal = get_current_time();;
	prog->philos[id].num_of_philos = args[0];
	prog->philos[id].time_to_die = args[1];
	prog->philos[id].time_to_eat = args[2];
	prog->philos[id].time_to_sleep = args[3];
	prog->philos[id].time_start = 0;
	prog->philos[id].dead = &prog->dead_flag;
	prog->philos[id].r_fork = &prog->forks[id];
	if (args[0] == 1)
		prog->philos[id].l_fork = &prog->forks[id];
	else if (id == 0)
		prog->philos[id].l_fork = &prog->forks[args[0] - 1];
	else
		prog->philos[id].l_fork = &prog->forks[id - 1];
	prog->philos[id].write_lock = &prog->write_lock;
	prog->philos[id].dead_lock = &prog->dead_lock;
	prog->philos[id].meal_lock = &prog->meal_lock;
}

void	ft_init_program(t_program *prog, int *args)
{
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->dead_flag = 0;
	prog->num_of_philos = args[0];
	if (args[4] >= 0)
		prog->num_times_to_eat = args[4];
}

void	ft_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	if (!(*philo->dead))
		printf("%d %d %s\n", (int)(get_current_time() - philo->time_start), philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	ft_kill(t_program *prog)
{
	pthread_mutex_lock(&prog->dead_lock);
	if (prog->dead_flag == 0)
		prog->dead_flag = 1;
	pthread_mutex_unlock(&prog->dead_lock);
}

int	ft_check_dead(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_lock(&prog->meal_lock);

		printf("DEBUG: Philosopher %d\n", i);
		printf("  current_time: %zu\n", get_current_time());
		printf("  time_meal:    %zu\n", prog->philos[i].time_meal);
		printf("  elapsed:      %zu\n", get_current_time() - prog->philos[i].time_meal);
		printf("  time_to_die:  %zu\n", prog->philos[i].time_to_die);
		printf("  eating:       %d\n", prog->philos[i].eating);
		if (get_current_time() - prog->philos[i].time_meal > prog->philos[i].time_to_die
			&& !(prog->philos[i].eating))
		{
			ft_kill(prog);
			ft_status(&prog->philos[i], "died");
			pthread_mutex_unlock(&prog->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_status(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->eating = 0;
	philo->time_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
}

void	*ft_fork(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_status(philo, "has taken a fork");
		while (!(*philo->dead)) // espera a morir
			usleep(100);
		pthread_mutex_unlock(philo->r_fork);
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
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_start = get_current_time();
	philo->time_meal = get_current_time();
	while (!(*(philo->dead)))
	{
		ft_fork(philo);
		ft_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_status(philo, "is thinking");
	}
	return (NULL);
}

int	ft_check_full(t_program *prog)
{
	int	full_philos;
	int	i;

	i = 0;
	full_philos = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (prog->num_times_to_eat > 0 &&
			prog->philos[i].meals_eaten >= prog->num_times_to_eat)
			full_philos++;
		pthread_mutex_unlock(&prog->meal_lock);
		i++;
	}
	if (prog->num_times_to_eat > 0 && full_philos == prog->num_of_philos)
		return (1);
	return (0);
}

void	*ft_monitoring(void *arg)
{
	t_program	*prog;

	prog = (t_program *)arg;
	while (1)
	{
		if (ft_check_dead(prog))
			break;
		if (ft_check_full(prog))
		{
			ft_kill(prog);
			break;
		}
		usleep(500);
	}
	return (NULL);
}

void	ft_thread(t_program *program)
{
	int	i;
	pthread_t	monitor;

	i = 0;
	while(i < program->num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, ft_routine, (void*)&program->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, ft_monitoring, (void*)&program);
	pthread_join(monitor, NULL);
	i = 0;
	while(i < program->num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}

void	ft_finish(t_program *prog)
{
	int	i;
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);
	i = 0;
	while(i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	return;
}

int	main(int argc, char **argv)
{
	int				args[5];
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				i;

	if (argc < 5 || argc > 6)
		return(1);
	ft_parse(args, argv, argc);
	ft_init_program(&program, args);
	program.philos = philos;
	program.forks = forks;
	i = 0;
	while(i < program.num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		ft_init_philos(&program, args, i);
		i++;
	}
	ft_thread(&program);
	ft_finish(&program);
	ft_exit(0);
}
