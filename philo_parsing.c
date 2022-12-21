/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:38:15 by nbled             #+#    #+#             */
/*   Updated: 2022/12/12 22:38:17 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (is_digit(str[i++]) == 0)
			return (0);
	return (1);
}

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	s;

	i = 0;
	result = 0;
	s = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
	i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s -= 2;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i] -48);
		i++;
	}
	return (result * s);
}

int	philo_parsing(t_big_brother *big_brother, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (is_number(argv[1]))
		big_brother->number_of_philosophers = ft_atoi(argv[1]);
	else
		return (0);
	if (is_number(argv[2]))
		big_brother->time_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (is_number(argv[3]))
		big_brother->time_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (is_number(argv[4]))
		big_brother->time_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	big_brother->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6 && is_number(argv[5]))
		big_brother->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else if (argc == 6)
		return (0);
	return (1);
}
