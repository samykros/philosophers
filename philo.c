/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:47:28 by spascual          #+#    #+#             */
/*   Updated: 2024/10/28 16:13:18 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// valgrind --leak-check=full ./philo 5 800 200 200
void	free_resources(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->philo)
	{
		while (i < rules->number_of_philosophers)
		{
			pthread_mutex_destroy(rules->philo[i]->p_mutex);
			free(rules->philo[i]);
			i++;
		}
		free(rules->philo);
		rules->philo = NULL;
	}
	i = 0;
	if (rules->fork_mutex)
	{
		while (i < rules->number_of_philosophers)
		{
			pthread_mutex_destroy(&rules->fork_mutex[i]);
			i++;
		}
		free(rules->fork_mutex);
		rules->fork_mutex = NULL;
	}
	if (rules->died_mutex)
	{
		pthread_mutex_destroy(rules->died_mutex);
		free(rules->died_mutex);
		rules->died_mutex = NULL;
	}
	if (rules->print_mutex)
	{
		pthread_mutex_destroy(rules->print_mutex);
		free(rules->print_mutex);
		rules->print_mutex = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor_thread;

	if (argc != 5 && argc != 6)
		return (printf("Wrong amoung of arguments\n"));
	if (init(&rules, argv) != 0 || input_checker(argv) == 0)
		return (printf("Wrong arguments\n"));
	if (ft_atoi(argv[1]) == 1)
	{
		usleep(ft_atoi(argv[2]));
		rules.died = 1;
		printf("\033[0;37m[%06d]  \033[0;34m[001] \033[0;31m"
			"died 💀\n", ft_atoi(argv[2]));
	}
	pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitor, &rules);
	loop(&rules);
	if (pthread_join(monitor_thread, NULL))
	{
		pthread_mutex_lock(rules.print_mutex);
		printf("Error joining thread for monitor\n");
		pthread_mutex_unlock(rules.print_mutex);
		return (1);
	}
	free_resources(&rules);
	return (0);
}
