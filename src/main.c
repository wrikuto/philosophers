/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:49:17 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/19 16:16:32 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	prepare_party(int argc, char **argv, t_tools *tools)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (-1);
	}
	if (set_situation((argv + 1), tools) == -1)
	{
		printf("Incorrect input type\n");
		return (-1);
	}
	if (build_up(tools) == -1)
	{
		printf("Malloc Error\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_tools	tools;

	i = 0;
	if (prepare_party(argc, argv, &tools) == -1)
		return (-1);
	while (is_philo_dead(&tools) == 0)
		usleep(1000);
	join_threads(&tools);
	free_philo_and_forks(&tools);
	pthread_mutex_destroy(&tools.lock);
	pthread_mutex_destroy(&tools.eat);
	pthread_mutex_destroy(&tools.decrease);
	while (i < tools.num_philo)
		pthread_mutex_destroy(&tools.forks[i++]);
	return (0);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}
