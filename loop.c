/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:06:02 by spascual          #+#    #+#             */
/*   Updated: 2024/10/28 16:09:48 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->rules->time_to_eat / 2);
	pthread_mutex_lock(philo->rules->died_mutex);
	while (philo->rules->died == 0)
	{
		pthread_mutex_unlock(philo->rules->died_mutex);
		take_forks(philo);
		philo_eat(philo);
		put_down_forks(philo);
		philo_sleep_think(philo);
		pthread_mutex_lock(philo->rules->died_mutex);
	}
	pthread_mutex_unlock(philo->rules->died_mutex);
	return (NULL);
}

void	loop(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_create(&rules->philo[i]->thread, NULL,
				philosopher_routine, rules->philo[i]))
		{
			pthread_mutex_lock(rules->print_mutex);
			printf("Error creating thread for philosopher %d\n", i + 1);
			pthread_mutex_unlock(rules->print_mutex);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_join(rules->philo[i]->thread, NULL))
		{
			pthread_mutex_lock(rules->print_mutex);
			printf("Error joining thread for philosopher %d\n", i + 1);
			pthread_mutex_unlock(rules->print_mutex);
			return ;
		}
		i++;
	}
}
