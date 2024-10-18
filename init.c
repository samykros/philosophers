/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:51:13 by spascual          #+#    #+#             */
/*   Updated: 2024/10/18 16:01:42 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_died_mutex(t_rules *rules)
{
	rules->died_mutex = malloc(sizeof(pthread_mutex_t));
	if (!rules->died_mutex)
	{
		free(rules->fork_mutex);
		free(rules->died_mutex);
		return (1);
	}
	if (pthread_mutex_init(rules->died_mutex, NULL) != 0)
	{
		free(rules->fork_mutex);
		free(rules->died_mutex);
		return (1);
	}
	return (0);
}

static int	init_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philo = malloc(rules->number_of_philosophers * sizeof(t_philo));
	rules->died = 0;
	if (!rules->philo)
		return (1);
	while (i <= (rules->number_of_philosophers - 1))
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].x_ate = 0;
		rules->philo[i].my_fork_id = i + 1;
		rules->philo[i].r_fork_id = i + 2;
		rules->philo[i].t_last_ate = get_time();
		rules->philo[i].rules = rules;
		i++;
	}
	i--;
	rules->philo[i].r_fork_id = 1;
	return (0);
}

static int	init_fork_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t)
			* rules->number_of_philosophers);
	if (!rules->fork_mutex)
		return (1);
	while (i < rules->number_of_philosophers)
	{
		if (pthread_mutex_init(&rules->fork_mutex[i], NULL) != 0)
		{
			i = 0;
			while (i-- > 0)
				pthread_mutex_destroy(&rules->fork_mutex[i]);
			free(rules->fork_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init(t_rules *rules, char **argv)
{
	rules->number_of_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->start_time = get_time();
	if (argv[5])
	{
		rules->nb_philo_must_eat = ft_atoi(argv[5]);
		if (rules->nb_philo_must_eat <= 0)
			return (1);
	}
	else
		rules->nb_philo_must_eat = -1;
	if (rules->number_of_philosophers < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (1);
	if (init_philosophers(rules) != 0)
		return (1);
	if (init_fork_mutex(rules) != 0 || init_died_mutex(rules) != 0)
		return (1);
	return (0);
}
