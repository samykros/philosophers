/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:18:39 by spascual          #+#    #+#             */
/*   Updated: 2024/10/17 16:32:54 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int message)
{
	int			time;
	long long	aux;

	aux = get_time();
	time = aux - philo->rules->start_time;
	pthread_mutex_lock(philo->rules->died_mutex);
	if (philo->rules->died == 0)
	{
		if (message == 1)
		{
			printf("%d %d has taken fork %d\n", time, philo->id, philo->my_fork_id);
			printf("%d %d has taken fork %d\n", time, philo->id, philo->r_fork_id);
		}
		else if (message == 2)
			printf("%d %d is eating\n", time, philo->id);
		else if (message == 3)
			printf("%d %d put down forks %d and %d\n", time, philo->id, philo->my_fork_id, philo->r_fork_id);
		else if (message == 4)
			printf("%d %d is sleeping\n", time, philo->id);
		else if (message == 5)
			printf("%d %d is thinking\n", time, philo->id);
	}
	pthread_mutex_unlock(philo->rules->died_mutex);
}

void	take_forks(t_philo *philo)
{
	int	temp;

	temp = philo->my_fork_id;
	if (philo->my_fork_id > philo->r_fork_id)
	{
		philo->my_fork_id = philo->r_fork_id;
		philo->r_fork_id = temp;
	}
	pthread_mutex_lock(&philo->rules->fork_mutex[philo->my_fork_id - 1]);
	pthread_mutex_lock(&philo->rules->fork_mutex[philo->r_fork_id - 1]);
	print_message(philo, 1);
}

void	philo_eat(t_philo *philo)
{
	philo->t_last_ate = get_time();
	print_message(philo, 2);
	ft_usleep(philo->rules->time_to_eat * 1000);
}

void	put_down_forks(t_philo *philo)
{
	philo->x_ate++;
	pthread_mutex_unlock(&philo->rules->fork_mutex[philo->my_fork_id - 1]);
	pthread_mutex_unlock(&philo->rules->fork_mutex[philo->r_fork_id - 1]);
	print_message(philo, 3);
}

void	philo_sleep_think(t_philo *philo)
{
	print_message(philo, 4);
	ft_usleep(philo->rules->time_to_sleep * 1000);
	print_message(philo, 5);
}
