/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:47:28 by spascual          #+#    #+#             */
/*   Updated: 2024/10/18 14:51:28 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_draft(t_rules *rules)
{
	free(rules->philo);
	free(rules->fork_mutex);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor_thread;

	if (argc != 5 && argc != 6)
		return (printf("Wrong amoung of arguments\n"));
	if (init(&rules, argv) != 0 || input_checker(argv) == 0)
		return (printf("Wrong arguments\n"));
	pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitor, &rules);
	loop(&rules);
	if (pthread_join(monitor_thread, NULL))
	{
		printf("Error joining thread for monitor\n");
		return (1);
	}
	free_draft(&rules);
	return (0);
}
