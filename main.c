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

void* test(t_philo *philo)
{
	if (philo->index % 2 == 1)
		printf("philosopher "RED"%d"END" is eating\n",philo->index);
	return (NULL);
}

void	*philo_init(t_big_brother *big_brother, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->time_until_death = 0;
	philo->dinner_count = 0;
	philo->index = index;
	philo->big_brother = big_brother;
	return (philo);
}

void*	big_brother_init(t_big_brother *big_brother)
{
	pthread_t	philo[big_brother->number_of_philosophers];
	int			i;

	i = 0;
	while (i < big_brother->number_of_philosophers)
	{
		pthread_create(philo + i, NULL, (void *)test, philo_init(big_brother, i));
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_big_brother	big_brother;
	pthread_mutex_t	write;
	pthread_t		bb;

	if (philo_parsing(&big_brother, argc, argv) == 0)
		return (0);
	//write = malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(&write, NULL);
	pthread_mutex_lock(&write);
	pthread_mutex_unlock(&write);
	pthread_create(&bb, NULL, (void *)big_brother_init, &big_brother);
	usleep(100000);
}
