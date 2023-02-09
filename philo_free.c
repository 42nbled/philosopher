/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:26:38 by nbled             #+#    #+#             */
/*   Updated: 2023/02/09 16:35:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	big_brother_clear(t_big_brother *big_brother)
{
	int	i;

	i = 1;
	pthread_mutex_destroy(&big_brother->write);
	pthread_mutex_destroy(&big_brother->death_check);
	while (i < big_brother->number_of_philosophers)
		pthread_mutex_destroy(&big_brother->fork[i++]);
	free(big_brother->time_until_death);
	free(big_brother->fork);
	free(big_brother);
}

void	philo_clear(t_big_brother *big_brother, pthread_t *philo)
{
	int	i;

    i = 0;
    while (i < big_brother->number_of_philosophers)
    {
		pthread_join(philo[i], NULL);
        free(&big_brother->philo[i]);
        i++;
    }
	free(big_brother->philo);
}
