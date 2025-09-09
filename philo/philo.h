/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:08:37 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/09 17:36:53 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

# define PHILO_MAX_COUNT 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_meal;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_start;
	int				num_of_philos;
	int				num_times_to_eat;
	volatile int	*death;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	int				num_times_to_eat;
	volatile int	death;
	size_t			time_to_die;
	size_t			start_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_program;

/* -------◊	AUXILIARY	◊------- */
int		ft_isnum(char *s);
int		ft_atoi(const char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	ft_exit(char *error, int signal);

/* -------◊	INITIALIZATION	◊------- */
void	ft_init_philos(t_program *prog, int *args, int id);
void	ft_init_program(t_program *prog, int *args);

/* -------◊	MAIN	◊------- */
void	*ft_parse(int *args, char **argv, int argc);
void	ft_thread(t_program *prog);
void	ft_destroy_mutex(t_program *prog, char *error, int signal);

/* -------◊	MONITOR	◊------- */
void	*ft_monitoring(void *arg);
int		ft_check_dead(t_program *prog);
int		ft_check_full(t_program *prog);
void	ft_update_round_phase(t_program *prog);

/* -------◊	PHILOSOPHERS	◊------- */
void	*ft_routine(void *arg);
int		ft_eat(t_philo *philo);
int		ft_status(t_philo *philo, char *str);

#endif