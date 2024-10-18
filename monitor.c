/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:44:21 by spascual          #+#    #+#             */
/*   Updated: 2024/10/18 15:06:37 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status(t_rules *rules)
{
	int	min_ate;
	int	i;

	min_ate = 1000000;
	i = 0;
	if (rules->nb_philo_must_eat == -1)
		return (0);
	while (i < rules->number_of_philosophers)
	{
		if (rules->philo[i].x_ate < min_ate)
			min_ate = rules->philo[i].x_ate;
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

int	starve(t_philo *philo)
{
	int			i;
	long long	aux;
	long long	time;

	i = 0;
	while (i < philo->rules->number_of_philosophers)
	{
		aux = get_time();
		time = aux - philo[i].t_last_ate;
		if (time > philo->rules->time_to_die)
			return (1);
		i++;
	}
	return (0);
}

void	check_philosopher_status(t_rules *rules, int i)
{
	t_philo		*philo;
	long long	current_time;
	int			time;

	philo = &rules->philo[i];
	current_time = get_time();
	time = current_time - rules->start_time;
	if (starve(rules->philo) == 1)
	{
		pthread_mutex_lock(rules->died_mutex);
		rules->died = 1;
		pthread_mutex_unlock(rules->died_mutex);
		printf("%d died\n", philo->id);
	}
	if (status(philo->rules) == 1)
		printf("%d Everyone ate\n", time);
}

void	monitor(t_rules *rules)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < rules->number_of_philosophers)
		{
			check_philosopher_status(rules, i);
			i++;
		}
		if (rules->died == 1)
			break ;
		ft_usleep(10000);
	}
}
