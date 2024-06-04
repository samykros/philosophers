/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:18:39 by spascual          #+#    #+#             */
/*   Updated: 2024/05/28 18:32:32 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int message)
{
	int	time;
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

// should i take separately?
void	take_forks(t_philo *philo)
{
	int	my_fork;
	int	right_fork;
	int	temp;

	my_fork = philo->my_fork_id;
	right_fork = philo->r_fork_id;
	temp = my_fork;
	if (my_fork > right_fork)
	{
		my_fork = right_fork;
		right_fork = temp;
	}
	pthread_mutex_lock(&philo->rules->fork_mutex[my_fork - 1]);
	pthread_mutex_lock(&philo->rules->fork_mutex[right_fork - 1]);
	print_message(philo, 1);
}

void	philo_eat(t_philo *philo)
{
	long long	aux;

	aux = get_time();
	philo->t_last_ate = aux - philo->rules->start_time;
	print_message(philo, 2);
	usleep(philo->rules->time_to_eat * 1000);
	philo->t_last_ate = 0;
}

void	put_down_forks(t_philo *philo)
{
	//pthread_mutex_lock(&philo->rules->x_ate_mutex[philo->x_ate]); // here
	philo->x_ate++;
	//pthread_mutex_unlock(&philo->rules->x_ate_mutex[philo->x_ate]); // here
	pthread_mutex_unlock(&philo->rules->fork_mutex[philo->my_fork_id - 1]);
	pthread_mutex_unlock(&philo->rules->fork_mutex[philo->r_fork_id - 1]);
	print_message(philo, 3);
}

void	philo_sleep_think(t_philo *philo)
{
	print_message(philo, 4);
	usleep(philo->rules->time_to_sleep * 1000);
	print_message(philo, 5);
}
