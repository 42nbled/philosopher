/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:27:29 by nbled             #+#    #+#             */
/*   Updated: 2023/02/18 02:44:44 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_first(t_philo *philo)
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

void	eat_sec(t_philo *philo)
{
	pthread_mutex_lock(philo->sec_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->first_fork);
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
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->sec_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->big_brother->time_to_sleep);
}

void	think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	usleep(500);
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
		if (philo->index % 2)
			eat_first(philo);
		else
			eat_sec(philo);
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
