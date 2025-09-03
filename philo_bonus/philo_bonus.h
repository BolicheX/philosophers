/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:08:37 by jose-jim          #+#    #+#             */
/*   Updated: 2025/09/02 21:27:14 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>

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
	pthread_t			death_thread;
	pid_t				pid;
	int					id;
	int					meals_eaten;
	size_t				time_to_die;
	size_t				time_meal;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				time_start;
	int					num_of_philos;
	int					num_times_to_eat;
	struct s_program	*prog;
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	int				dead_flag;
	size_t			start_time;
	sem_t			*meal_sem;
	sem_t			*write_sem;
	sem_t			*forks_sem;
	sem_t			*full_sem;
	sem_t			*table_sem;
	t_philo			*philos;
}					t_program;

/* -------◊	AUXILIARY	◊------- */
int		ft_isnum(char *s);
int		ft_atoi(const char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

/* -------◊	INIT AND EXIT◊------- */
void	ft_init_philos(t_program *prog, int *args, int id);
void	ft_init_program(t_program *prog, int *args);
void	ft_finish(t_program *prog, char *error, int parent, int signal);
void	ft_exit(char *error, int signal);

/* -------◊	MAIN	◊------- */
void	*ft_parse(int *args, char **argv, int argc);
void	ft_thread(t_program *prog);
void	ft_destroy_mutex(t_program *prog);

/* -------◊	MONITOR	◊------- */
void	*ft_check_dead(void *arg);
void	*ft_check_full(void *arg);
void	ft_kill(t_program *prog);

/* -------◊	PHILOSOPHERS	◊------- */
void	ft_philo_born(t_philo *philo);
void	ft_routine(t_philo *philo);
void	ft_status(t_philo *philo, char *str);

#endif