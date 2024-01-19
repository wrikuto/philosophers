/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:49:01 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/19 16:51:06 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	just_die(int i, t_tools *tools)
{
	printf("%ld %d died\n", \
			elapsed_time(tools->start_time), tools->philo[i].id);
	if (tools->num_philo == 1 && tools->end == true)
		pthread_mutex_unlock(&tools->forks[0]);
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
				just_die(i, tools);
			return (1);
		}
		i++;
	}
	return (0);
}
