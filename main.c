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

void	*philo_init(t_big_brother *big_brother, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	big_brother->time_until_death[i - 1]
		= big_brother->start_time + big_brother->time_to_die;
	philo->index = i;
	philo->dinner_count = 0;
	philo->first_fork = &big_brother->fork[i - 1];
	if (i == big_brother->number_of_philosophers)
		philo->sec_fork = &big_brother->fork[0];
	else
		philo->sec_fork = &big_brother->fork[i];
	philo->big_brother = big_brother;
	big_brother->philo[i - 1] = *philo;
	return (philo);
}

int	big_brother_init(t_big_brother *big_brother)
{
	int			i;

	i = 0;
	big_brother->philo = malloc(sizeof (t_philo)
			* big_brother->number_of_philosophers);
	if (!big_brother->philo)
		return (0);
	big_brother->fork = malloc(sizeof (pthread_mutex_t)
			* big_brother->number_of_philosophers);
	if (!big_brother->fork)
		return (0);
	big_brother->time_until_death
		= malloc(sizeof(time_t) * big_brother->number_of_philosophers);
	if (!big_brother->time_until_death)
		return (0);
	while (i < big_brother->number_of_philosophers)
		pthread_mutex_init(&big_brother->fork[i++], NULL);
	pthread_mutex_init(&big_brother->write, NULL);
	pthread_mutex_init(&big_brother->death_check, NULL);
	big_brother->who_finished = 0;
	big_brother->start_time = get_time();
	return (1);
}

pthread_t	*philo_launch(t_big_brother *big_brother)
{
	pthread_t	*philo;
	int			i;

	i = 1;
	philo = malloc(sizeof(pthread_t) * big_brother->number_of_philosophers);
	if (!philo)
		return ((void *) NULL);
	while (i <= big_brother->number_of_philosophers)
	{
		if (pthread_create(philo + (i - 1), NULL, (void *)philo_th,
				philo_init(big_brother, i)))
			return ((void *) NULL);
		i += 2;
	}
	i = 2;
	ft_usleep(5);
	while (i <= big_brother->number_of_philosophers)
	{
		if (pthread_create(philo + (i - 1), NULL, (void *)philo_th,
				philo_init(big_brother, i)))
			return ((void *) NULL);
		i += 2;
	}
	return (philo);
}

void	death_cycle(t_big_brother *big_brother, int i)
{
	usleep (2000);
	while (1)
	{
		if (i == big_brother->number_of_philosophers)
			i = 0;
		pthread_mutex_lock(&big_brother->death_check);
		if (big_brother->time_until_death[i] <= get_time())
		{
			big_brother->who_finished = big_brother->number_of_philosophers;
			pthread_mutex_unlock(&big_brother->death_check);
			usleep(10);
			printf("%ld %d died\n", get_time() - big_brother->start_time, i + 1);
			return ;
		}
		if (big_brother->who_finished == big_brother->number_of_philosophers)
		{
			big_brother->who_finished = big_brother->number_of_philosophers;
			pthread_mutex_unlock(&big_brother->death_check);
			usleep(10);
			return ;
		}
		pthread_mutex_unlock(&big_brother->death_check);
		usleep(500);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_big_brother	*big_brother;
	pthread_t		*philo;

	big_brother = malloc(sizeof(t_big_brother));
	if (!big_brother)
		return (0);
	if (philo_parsing(big_brother, argc, argv) == 0)
	{
		printf(RED"Error\n"END);
		free(big_brother);
		return (0);
	}
	if (big_brother_init(big_brother) == 1)
	{
		philo = philo_launch(big_brother);
		if (philo)
			death_cycle(big_brother, 0);
		philo_clear(big_brother, philo);
	}
	big_brother_clear(big_brother);
}
