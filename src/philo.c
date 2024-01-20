/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:03:14 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/20 17:08:17 by wrikuto          ###   ########.fr       */
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
		return ;
	print_philo_status("has taken a fork", philo->id, philo->tools);
	set_m_t(philo);
	if (philo->c_meals != -1)
	{
		pthread_mutex_lock(&philo->tools->decrease);
		philo->c_meals++;
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
	while ((check_end(philo->tools) != 1))
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
