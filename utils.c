/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:00:44 by spascual          #+#    #+#             */
/*   Updated: 2024/05/23 19:05:03 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	input_checker(char **argv)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec * 1000LL) + (time_now.tv_usec / 1000));
}

void	print_rules(const t_rules *rules)
{
	//printf("number_of_philosophers: %d\n", rules->number_of_philosophers);
	//printf("time_to_die: %d\n", rules->time_to_die);
	//printf("time_to_eat: %d\n", rules->time_to_eat);
	//printf("time_to_sleep: %d\n", rules->time_to_sleep);
	//printf("number_eat: %d\n", rules->nb_philo_must_eat);
	//printf("died: %d\n", rules->died);
	//printf("ate: %d\n", rules->ate);
	printf("\nFirst (array starts 0): ------------- \n");
	printf("id: %d\n", rules->philo[0].id);
	printf("x_ate: %d\n", rules->philo[0].x_ate);
	printf("my_fork_id: %d\n", rules->philo[0].my_fork_id);
	printf("r_fork_id: %d\n", rules->philo[0].r_fork_id);
	printf("\nlast:                   ------------- \n");
	printf("id: %d\n", rules->philo[rules->number_of_philosophers - 1].id);
	printf("x_ate: %d\n", rules->philo[rules->number_of_philosophers - 1].x_ate);
	printf("my_fork_id: %d\n", rules->philo[rules->number_of_philosophers - 1].my_fork_id);
	printf("r_fork_id: %d\n", rules->philo[rules->number_of_philosophers - 1].r_fork_id);
	printf("t_last_ate: %lld\n", rules->philo[rules->number_of_philosophers - 1].t_last_ate);
	printf("\n");
}
