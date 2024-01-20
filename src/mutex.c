/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:58:10 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/20 16:15:37 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_end(t_tools *tools)
{
	int	status;

	pthread_mutex_lock(&tools->lock);
	if (tools->end)
		status = 1;
	else
		status = 0;
	pthread_mutex_unlock(&tools->lock);
	return (status);
}

int	change_end(t_tools *tools)
{
	pthread_mutex_lock(&tools->lock);
	tools->end = true;
	pthread_mutex_unlock(&tools->lock);
	return (1);
}

void	set_m_t(t_philo *philo)
{
	pthread_mutex_lock(&philo->tools->eat);
	philo->time_last_meal = get_ms();
	pthread_mutex_unlock(&philo->tools->eat);
}

long	read_m_t(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->tools->eat);
	last_meal_time = philo->time_last_meal;
	pthread_mutex_unlock(&philo->tools->eat);
	return (last_meal_time);
}
