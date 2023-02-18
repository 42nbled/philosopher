/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:27:29 by nbled             #+#    #+#             */
/*   Updated: 2023/02/17 22:08:14 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->big_brother->write);
	pthread_mutex_lock(&philo->big_brother->death_check);
	if (philo->big_brother->who_finished
		< philo->big_brother->number_of_philosophers)
		printf("%ld %d %s\n", get_time()
			- philo->big_brother->start_time, philo->index, str);
	pthread_mutex_unlock(&philo->big_brother->death_check);
	pthread_mutex_unlock(&philo->big_brother->write);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->sec_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->big_brother->death_check);
	philo->big_brother->time_until_death[philo->index
		- 1] = get_time() + philo->big_brother->time_to_die;
	pthread_mutex_unlock(&philo->big_brother->death_check);
	ft_usleep(philo->big_brother->time_to_eat);
	philo->dinner_count++;
	pthread_mutex_lock(&philo->big_brother->death_check);
	if (philo->dinner_count == philo->big_brother->number_of_eat)
		philo->big_brother->who_finished++;
	pthread_mutex_unlock(&philo->big_brother->death_check);
	pthread_mutex_unlock(philo->sec_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->big_brother->time_to_sleep);
}

void	think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	*philo_th(t_philo *philo)
{
	if (philo->big_brother->number_of_philosophers == 1)
	{
		ft_print(philo, "is thinking");
		ft_print(philo, "has taken a fork");
		free(philo);
		return (NULL);
	}
	while (1)
	{
		think(philo);
		eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->big_brother->death_check);
		if (philo->big_brother->who_finished
			>= philo->big_brother->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo->big_brother->death_check);
			free(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->big_brother->death_check);
	}
}
