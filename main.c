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
	philo->first_fork = &big_brother->fork[i];
	if (i == big_brother->number_of_philosophers)
		philo->sec_fork = &big_brother->fork[1];
	else
		philo->sec_fork = &big_brother->fork[i + 1];
	philo->big_brother = big_brother;
	return (philo);
}

void	big_brother_init(t_big_brother *big_brother)
{
	int			i;

	i = 1;
	big_brother->fork = malloc(sizeof (pthread_mutex_t)
			* big_brother->number_of_philosophers);
	if (!big_brother->fork)
		return ;
	while (i <= big_brother->number_of_philosophers)
		pthread_mutex_init(&big_brother->fork[i++], NULL);
	pthread_mutex_init(&big_brother->write, NULL);
	pthread_mutex_init(&big_brother->death_check, NULL);
	big_brother->who_finished = 0;
	big_brother->start_time = get_time();
	big_brother->time_until_death
		= malloc(sizeof(time_t) * big_brother->number_of_philosophers);
	if (!big_brother->fork)
		return ;
}

void	philo_launch(t_big_brother *big_brother)
{
	pthread_t	*philo;
	int			i;

	philo = malloc(sizeof(pthread_t) * big_brother->number_of_philosophers);
	if (!philo)
		return ;
	i = 1;
	while (i % 2 == 1 && i <= big_brother->number_of_philosophers)
	{
		pthread_create(philo + i, NULL, (void *)philo_th,
			philo_init(big_brother, i));
		i += 2;
	}
	i = 2;
	ft_usleep(20);
	while (i % 2 == 0 && i <= big_brother->number_of_philosophers)
	{
		pthread_create(philo + i, NULL, (void *)philo_th,
			philo_init(big_brother, i));
		i += 2;
	}
}

void	death_cycle(t_big_brother *big_brother, int i)
{
	while (1)
	{
		if (i == big_brother->number_of_philosophers)
			i = 0;
		pthread_mutex_lock(&big_brother->death_check);
		if (big_brother->time_until_death[i] <= get_time())
		{
			pthread_mutex_lock(&big_brother->write);
			usleep(10);
			printf("%ld %d died\n", get_time()
				- big_brother->start_time, i + 1);
			return ;
		}
		if (big_brother->who_finished == big_brother->number_of_philosophers)
		{
			pthread_mutex_lock(&big_brother->write);
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
	t_big_brother	big_brother;
	int				i;

	i = 1;
	if (philo_parsing(&big_brother, argc, argv) == 0)
	{
		printf(RED"Error\n"END);
		return (0);
	}
	big_brother_init(&big_brother);
	philo_launch(&big_brother);
	death_cycle(&big_brother, 0);
}
