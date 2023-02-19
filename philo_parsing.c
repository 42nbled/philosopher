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

unsigned int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (nptr[i] == '-')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i] -48);
		i++;
	}
	return (result);
}

int	philo_parsing(t_big_brother *big_brother, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (is_number(argv[1]) && ft_atoi(argv[1]) > 0 && ft_atoi(argv[1]) < 1000)
		big_brother->number_of_philosophers = ft_atoi(argv[1]);
	else
		return (0);
	if (is_number(argv[2]) && ft_atoi(argv[2]) > 0)
		big_brother->time_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (is_number(argv[3]) && ft_atoi(argv[3]) > 0)
		big_brother->time_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (is_number(argv[4]) && ft_atoi(argv[4]) > 0)
		big_brother->time_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	big_brother->number_of_eat = -1;
	if (argc == 6 && is_number(argv[5]) && ft_atoi(argv[5]) > 0)
		big_brother->number_of_eat
			= ft_atoi(argv[5]);
	else if (argc == 6)
		return (0);
	return (1);
}
