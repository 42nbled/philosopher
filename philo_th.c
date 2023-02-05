/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:27:29 by nbled             #+#    #+#             */
/*   Updated: 2023/02/02 22:27:31 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (philo->big_brother->is_alive[philo->index - 1] != 1)
	{
		pthread_mutex_lock(&philo->big_brother->write);
		printf("%ld %d has taken a fork\n", get_time()
			- philo->big_brother->start_time, philo->index);
		pthread_mutex_unlock(&philo->big_brother->write);
		pthread_mutex_lock(philo->sec_fork);
		if (philo->big_brother->is_alive[philo->index - 1] != 1)
		{
			pthread_mutex_lock(&philo->big_brother->write);
			printf("%ld %d has taken a fork\n", get_time()
				- philo->big_brother->start_time, philo->index);
			pthread_mutex_unlock(&philo->big_brother->write);

			if (philo->big_brother->is_alive[philo->index - 1] != 1)
			{
				pthread_mutex_lock(&philo->big_brother->write);
				printf("%ld %d is eating\n", get_time()
					- philo->big_brother->start_time, philo->index);
				pthread_mutex_unlock(&philo->big_brother->write);

				pthread_mutex_lock(&philo->big_brother->death_check);
				philo->big_brother->time_until_death[philo->index
					- 1] = get_time() + philo->big_brother->time_to_die;
				pthread_mutex_unlock(&philo->big_brother->death_check);
				philo->dinner_count = 0;
				ft_usleep(philo->big_brother->time_to_eat);
			}
		}
		pthread_mutex_unlock(philo->sec_fork);
	}
	pthread_mutex_unlock(philo->first_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld %d is sleeping\n", get_time()
		- philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
	ft_usleep(philo->big_brother->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld %d is thinking\n", get_time()
		- philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
}

void	*philo_th(t_philo *philo)
{
	while (philo->big_brother->is_alive[philo->index - 1] != 1)
	{
		if (philo->big_brother->is_alive[philo->index - 1] != 1)
			think(philo);
		if (philo->big_brother->is_alive[philo->index - 1] != 1)
			eat(philo);
		if (philo->big_brother->is_alive[philo->index - 1] != 1)
			ft_sleep(philo);
	}
	return (NULL);
}
