/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:18:39 by spascual          #+#    #+#             */
/*   Updated: 2024/10/18 16:06:59 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int message)
{
	long long	time;

	time = get_time() - philo->rules->start_time;
	pthread_mutex_lock(philo->rules->died_mutex);
	if (philo->rules->died == 0)
	{
		if (message == 1)
		{
			printf("\033[0;37m[%06lld]  \033[0;34m[%03d] \033[0;36m" 
				"has taken fork %d 🍴\n", time, philo->id, philo->my_fork_id);
			printf("\033[0;37m[%06lld]  \033[0;34m[%03d] \033[0;36m" 
				"has taken fork %d 🍴\n", time, philo->id, philo->r_fork_id);
		}
		else if (message == 2)
			printf("\033[0;37m[%06lld]  \033[0;34m[%03d] \033[0;33m" 
				"is eating 🍝\n", time, philo->id);
		else if (message == 4)
			printf("\033[0;37m[%06lld]  \033[0;34m[%03d] \033[0;35m"
				"is sleeping 🌙\n", time, philo->id);
		else if (message == 5)
			printf("\033[0;37m[%06lld]  \033[0;34m[%03d] \033[0;30m"
				"is thinking 💭\n", time, philo->id);
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
}

void	philo_sleep_think(t_philo *philo)
{
	print_message(philo, 4);
	ft_usleep(philo->rules->time_to_sleep * 1000);
	print_message(philo, 5);
}
