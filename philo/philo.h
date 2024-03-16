/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:12:55 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/11 20:39:25 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define LEFT	0
# define RIGHT	1

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_input
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals;
}	t_input;

typedef struct s_philo
{
	pthread_t		thread;
	int				last_meal;
	int				last_sleep;
	struct timeval	current;
	int				id;
	struct s_table	*table;
	int				nb_eat;
	bool			is_alive;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	bool			has_right_fork;
	bool			has_left_fork;
	struct s_fork	*right_fork;
	struct s_fork	*left_fork;
}	t_philo;

typedef struct s_fork
{
	bool			available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table
{
	struct s_input	input;
	struct s_philo	*philo;
	struct s_fork	*forks;
	bool			dessert;
	int				start;
	pthread_mutex_t	lock_dessert;
	pthread_mutex_t	lock_printf;
}	t_table;

int		ft_atoi(char *str);
bool	fail_to(bool v);
bool	wrong_number_of_arguments(int argc);
bool	initialise(t_table *table, int argc, char **argv);
void	clear_table(t_table *table);
void	destroy_all_mutex(t_table *table);
bool	start_diner(t_table *table);
void	*routine(void *arg);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	a_philosopher_is_dead(t_table *table);
void	philosopher_dies_from_starvation(t_philo *philo);
bool	fork_available(t_fork *fork);
void	take_fork(t_fork *fork, t_philo *philo, bool hand);
void	put_forks(t_philo *philo);
int		time_ms(struct timeval current);
void	printf_time(t_philo *philo, char *s);

#endif