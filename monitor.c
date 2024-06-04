/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:44:21 by spascual          #+#    #+#             */
/*   Updated: 2024/05/28 19:01:53 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int status(t_rules *rules)
{
	int min_ate = 1000000;
	int i = 0;

	if (rules->nb_philo_must_eat == -1)
		return (0);
	while (i < rules->number_of_philosophers)
	{
		//pthread_mutex_lock(&rules->x_ate_mutex[rules->philo->x_ate]); // here
		if (rules->philo[i].x_ate < min_ate)
			min_ate = rules->philo[i].x_ate;
		//pthread_mutex_unlock(&rules->x_ate_mutex[rules->philo->x_ate]); // here
		i++;
	}
	if (min_ate == rules->nb_philo_must_eat)
	{
		pthread_mutex_lock(rules->died_mutex);
		rules->died = 1;
		pthread_mutex_unlock(rules->died_mutex);
		return (1);
	}
	return (0);
}

void	t_last_ate_actualized(t_philo *philo)
{
	int			i;
	long long	aux;

	i = 0;
	aux = get_time();
	while (philo[i])
	{
		philo[i].t_last_ate = aux - philo->rules->start_time;
	}
}

void	monitor(t_rules *rules)
{
	int	i;
	t_philo *philo;
	long long current_time;
	//long long time_since_last_eat;
	int time;

	while (1)
	{
		i = 0;
		while (i < rules->number_of_philosophers)
		{
			philo = &rules->philo[i];
			current_time = get_time();
			//time_since_last_eat = current_time - philo->t_last_ate;
			time = current_time - rules->start_time;
			printf("TIME CHECK: %lld // %d // %d\n", philo->t_last_ate, time, philo->id); // FIX THIS
			if (philo->t_last_ate > rules->time_to_die)
			{
				pthread_mutex_lock(rules->died_mutex);
				rules->died = 1;
				pthread_mutex_unlock(rules->died_mutex);
				printf("%d %lld %d died\n", time , philo->t_last_ate, philo->id);
			}
			if (status(philo->rules) == 1)
			{
				printf("%d Everyone ate\n", time);
				break;
			}
			i++;
		}
		if (rules->died == 1)
			break;
		usleep(10000);
	}
}
