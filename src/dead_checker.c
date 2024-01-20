/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:49:01 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/20 17:07:53 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	just_die(int i, t_tools *tools)
{
	printf("%ld %d died\n", \
			elapsed_time(tools->start_time), tools->philo[i].id);
	if (tools->num_philo == 1)
		pthread_mutex_unlock(&tools->forks[0]);
}

static void	get_diffmeal_and_meal( \
			long *diff_meal, int *meals, t_tools *tools, int i)
{
	pthread_mutex_lock(&tools->decrease);
	*diff_meal = get_ms() - read_m_t(&tools->philo[i]);
	*meals = tools->philo[i].c_meals;
	pthread_mutex_unlock(&tools->decrease);
}

int	is_finish_or_dead(t_tools *tools)
{
	int		i;
	int		meals;
	int		chk_eatup;
	long	diff_meal;

	i = 0;
	chk_eatup = 0;
	while (i < tools->num_philo)
	{
		get_diffmeal_and_meal(&diff_meal, &meals, tools, i);
		if (tools->time_dead < diff_meal)
		{
			pthread_mutex_lock(&tools->decrease);
			just_die(i, tools);
			return (change_end(tools));
		}
		pthread_mutex_lock(&tools->decrease);
		if (tools->eat_up <= tools->philo[i].c_meals && tools->eat_up != -1)
			chk_eatup += 1;
		pthread_mutex_unlock(&tools->decrease);
		i++;
	}
	if (tools->num_philo <= chk_eatup)
		return (change_end(tools));
	return (0);
}
