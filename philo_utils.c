/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:11:48 by nbled             #+#    #+#             */
/*   Updated: 2023/02/08 07:11:50 by nbled            ###   ########.fr       */
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
