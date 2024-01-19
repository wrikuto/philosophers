/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:03:14 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/19 16:12:40 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_sleep(int time)
{
	long	start;
	long	elapsed;

	start = get_ms();
	elapsed = 0;
	while (elapsed < time)
	{
		usleep(time * 1000);
		elapsed = get_ms() - start;
	}
}

static int	get_right_fork(t_philo *philo)
{
	if (philo->id == 0)
		return (philo->tools->num_philo - 1);
	else
		return (philo->id - 1);
}

static void	eating(t_philo *philo)
{
	int	r_fork;

	r_fork = get_right_fork(philo);
	pthread_mutex_lock(&philo->tools->forks[r_fork]);
	print_philo_status("has taken a fork", philo->id, philo->tools);
	pthread_mutex_lock(&philo->tools->forks[philo->id]);
	if (philo->tools->num_philo == 1)
	{
		pthread_mutex_unlock(&philo->tools->forks[0]);
		return ;
	}
	print_philo_status("has taken a fork", philo->id, philo->tools);
	set_m_t(philo);
	if (philo->c_meals != -1)
	{
		pthread_mutex_lock(&philo->tools->decrease);
		philo->c_meals--;
		pthread_mutex_unlock(&philo->tools->decrease);
	}
	print_philo_status("is eating", philo->id, philo->tools);
	ft_sleep(philo->tools->time_eat);
	pthread_mutex_unlock(&philo->tools->forks[r_fork]);
	pthread_mutex_unlock(&philo->tools->forks[philo->id]);
	return ;
}

void	*philo_life(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(philo->tools->time_eat * 1000);
	while ((check_end(philo->tools) != 1) && (philo->c_meals != 0))
	{
		print_philo_status("is thinking", philo->id, philo->tools);
		eating(philo);
		if (philo->tools->num_philo == 1)
			return (NULL);
		print_philo_status("is sleeping", philo->id, philo->tools);
		ft_sleep(philo->tools->time_sleep);
	}
	return (NULL);
}

int	is_philo_dead(t_tools *tools)
{
	int		i;
	int		meals;
	long	diff_meal;

	i = 0;
	while (i < tools->num_philo)
	{
		pthread_mutex_lock(&tools->decrease);
		diff_meal = get_ms() - read_m_t(&tools->philo[i]);
		meals = tools->philo[i].c_meals;
		pthread_mutex_unlock(&tools->decrease);
		if (tools->time_dead < diff_meal || meals == 0)
		{
			pthread_mutex_lock(&tools->decrease);
			change_end(tools);
			if (tools->philo[i].c_meals != 0)
			{
				printf("%ld %d died\n", \
						elapsed_time(tools->start_time), tools->philo[i].id);
				if (tools->num_philo == 1 && tools->end == true)
					pthread_mutex_unlock(&tools->forks[0]);
			}
			return (1);
		}
		i++;
	}
	return (0);
}
