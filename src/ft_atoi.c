/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:18 by wrikuto           #+#    #+#             */
/*   Updated: 2024/01/19 19:48:32 by wrikuto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static	int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = ft_isspace(str);
	sign = 1 + ((str[i] == '-') * -2);
	num = 0;
	if (str[i] == '-' )
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (((num > LONG_MAX / 10) && ft_isdigit(str[i]) == 1) || \
			((num == LONG_MAX / 10) && str[i] > (LONG_MAX % 10) + '0'))
		{
			if (sign == -1)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
	}
	return ((int)(num * sign));
}
