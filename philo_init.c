/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:19:48 by nbled             #+#    #+#             */
/*   Updated: 2023/02/19 17:33:13 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_init(t_big_brother *big_brother, t_philo *philo, int i)
{
	philo->first_fork = &big_brother->fork[i - 1];
	if (i == big_brother->number_of_philosophers)
		philo->sec_fork = &big_brother->fork[0];
	else
		philo->sec_fork = &big_brother->fork[i];
	return ;
}

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
	fork_init(big_brother, philo, i);
	philo->big_brother = big_brother;
	big_brother->philo[i - 1] = *philo;
	return (philo);
}
