/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:49:15 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/19 16:50:20 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			time_last_meal;
	int				c_meals;
	struct s_tools	*tools;
}				t_philo;

typedef struct s_tools
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	eat;
	pthread_mutex_t	decrease;
	bool			end;
	long			start_time;
	int				num_philo;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				eat_up;
}				t_tools;

// prepare
int		set_situation(char **arg, t_tools *tools);
int		build_up(t_tools *tools);

// ft_atoi.c
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

// philo.c
int		is_philo_dead(t_tools *tools);
void	*philo_life(void *tmp);

// utils.c
int		join_threads(t_tools *tools);
void	free_philo_and_forks(t_tools *tools);
void	print_philo_status(char *str, int id, t_tools *tools);

// dead_checker.c
int		is_philo_dead(t_tools *tools);

// mutex.c
int		check_end(t_tools *tools);
void	change_end(t_tools *tools);
void	set_m_t(t_philo *philo);
long	read_m_t(t_philo *philo);

// time.c
long	elapsed_time(long start);

// mutex
long	get_ms(void);

#endif