/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:12:27 by spascual          #+#    #+#             */
/*   Updated: 2024/10/28 16:12:38 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				x_ate;
	int				my_fork_id;
	int				r_fork_id;
	long long		t_last_ate;
	struct s_rules	*rules;
	pthread_t		thread;
	pthread_mutex_t	*p_mutex;
}				t_philo;

typedef struct s_rules
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo_must_eat;
	int				died;
	long long		start_time;
	struct s_philo	**philo;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*died_mutex;
	pthread_mutex_t	*print_mutex;
}				t_rules;

int			init(t_rules *philo, char **argv);
int			ft_atoi(char *str);
int			input_checker(char **argv);
void		loop(t_rules *rules);
long long	get_time(void);
void		*philosopher_routine(void *arg);
void		take_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		philo_sleep_think(t_philo *philo);
void		monitor(t_rules *rules);
void		ft_usleep(int ms);
void		free_resources(t_rules *rules);

#endif
