/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:32:05 by nbled             #+#    #+#             */
/*   Updated: 2022/12/12 22:32:08 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32;1m"
# define YELLOW  "\x1b[33;1m"
# define BLUE    "\x1b[34;1m"
# define MAGENTA "\x1b[35;1m"
# define CYAN    "\x1b[36;1m"
# define END    "\x1b[0m"

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_big_brother
{
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	death_check;
	time_t			start_time;
	time_t			*time_until_death;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				who_finished;
}			t_big_brother;

typedef struct s_philo
{
	t_big_brother	*big_brother;
	int				index;
	pthread_t		philo;
	int				dinner_count;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*sec_fork;
}			t_philo;

int		philo_parsing(t_big_brother *big_brother, int argc, char **argv);
void	*philo_init(t_big_brother *big_brother, int i);
void	*philo_th(t_philo *philo);
void	ft_print(t_philo *philo, char *str);
time_t	get_time(void);
void	ft_usleep(int time);
void	big_brother_clear(t_big_brother *big_brother);
void	philo_clear(t_big_brother *big_brother, pthread_t	*philo);
#endif