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
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld ""%d"" has taken a ""fork\n", get_time() - philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
	pthread_mutex_lock(philo->sec_fork);
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld ""%d"" has taken a ""fork\n", get_time() - philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld ""%d"" is ""eating\n", get_time() - philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
	ft_usleep(philo->big_brother->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->sec_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld ""%d"" is ""sleeping\n", get_time() - philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
	ft_usleep(philo->big_brother->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->big_brother->write);
	printf("%ld ""%d"" is ""thinking\n", get_time() - philo->big_brother->start_time, philo->index);
	pthread_mutex_unlock(&philo->big_brother->write);
}

void*	philo_th(t_philo *philo)
{
	while (1)
	{
		think(philo);
		eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
