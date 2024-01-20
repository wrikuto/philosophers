/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_party.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:50:47 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/20 15:44:04 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	arg_check(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i] != NULL)
	{
		j = 0;
		while (arg[i][j] != '\0')
		{
			if (j != 0 && ft_isdigit(arg[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	set_situation(char **arg, t_tools *tools)
{
	if (arg_check(arg) == -1)
		return (-1);
	tools->start_time = get_ms();
	tools->end = false;
	tools->num_philo = ft_atoi(arg[0]);
	tools->time_dead = ft_atoi(arg[1]);
	tools->time_eat = ft_atoi(arg[2]);
	tools->time_sleep = ft_atoi(arg[3]);
	if (arg[4] != NULL)
	{
		tools->eat_up = ft_atoi(arg[4]);
		if (tools->eat_up < 0)
			return (-1);
	}
	else
		tools->eat_up = -1;
	if (tools->num_philo <= 0 || tools->time_dead <= 0 || tools->time_eat <= 0 \
	|| tools->time_sleep <= 0)
		return (-1);
	return (0);
}

static int	malloc_and_mutexinit(t_tools *tools)
{
	if (pthread_mutex_init(&tools->lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&tools->eat, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&tools->decrease, NULL) != 0)
		return (-1);
	tools->philo = malloc(sizeof(t_philo) * tools->num_philo);
	if (tools->philo == NULL)
		return (-1);
	tools->forks = malloc(sizeof(pthread_mutex_t) * tools->num_philo);
	if (tools->forks == NULL)
	{
		free(tools->philo);
		return (-1);
	}
	return (0);
}

static int	generate_philo(t_tools *tools, int i)
{
	tools->philo[i].id = i;
	tools->philo[i].time_last_meal = get_ms();
	tools->philo[i].tools = tools;
	tools->philo[i].c_meals = 0;
	if (pthread_create \
	(&tools->philo[i].thread, NULL, &philo_life, &tools->philo[i]) == 1)
		return (1);
	return (0);
}

int	build_up(t_tools *tools)
{
	int	i;

	if (malloc_and_mutexinit(tools) == -1)
		return (-1);
	i = 0;
	while (i < tools->num_philo)
	{
		if (pthread_mutex_init(&tools->forks[i++], NULL))
		{
			free_philo_and_forks(tools);
			return (-1);
		}
	}
	i = 0;
	while (i < tools->num_philo)
	{
		if (generate_philo(tools, i))
		{
			free_philo_and_forks(tools);
			return (-1);
		}
		i++;
	}
	return (1);
}
