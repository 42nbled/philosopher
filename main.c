/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:19:48 by nbled             #+#    #+#             */
/*   Updated: 2022/12/12 21:19:50 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time)
{
	usleep(time * 1000);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*philo_init(t_big_brother *big_brother, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->time_until_death = 0;
	philo->dinner_count = 0;
	philo->index = i;
	philo->first_fork = &big_brother->fork[i];
	if (i == big_brother->number_of_philosophers)
		philo->sec_fork = &big_brother->fork[1];
	else
		philo->sec_fork = &big_brother->fork[i + 1];
	philo->big_brother = big_brother;
	return (philo);
}

void*	big_brother_init(t_big_brother *big_brother)
{
	pthread_t	philo[big_brother->number_of_philosophers];
	int			i;

	i = 1;
	pthread_mutex_init(&big_brother->write, NULL);
	big_brother->fork = malloc(sizeof(pthread_mutex_t) *big_brother->number_of_philosophers);
	if (!big_brother->fork)
		return (NULL);
	while (i <= big_brother->number_of_philosophers)
		pthread_mutex_init(&big_brother->fork[i++], NULL);
	i = 1;
	big_brother->start_time = get_time();
	while (i % 2 == 1 && i <= big_brother->number_of_philosophers)
	{
		pthread_create(philo + i, NULL, (void *)philo_th, philo_init(big_brother, i));
		i+=2;
	}
	i = 2;
	ft_usleep(20);
	while (i % 2 == 0 && i <= big_brother->number_of_philosophers)
	{
		pthread_create(philo + i, NULL, (void *)philo_th, philo_init(big_brother, i));
		i+=2;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_big_brother	big_brother;
	pthread_t		bb;

	if (philo_parsing(&big_brother, argc, argv) == 0)
	{
		printf(RED"Error\n"END);
		return (0);
	}
	pthread_create(&bb, NULL, (void *)big_brother_init, &big_brother);
	while (1)
	{
		
	}
}