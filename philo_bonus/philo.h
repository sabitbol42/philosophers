/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:12:55 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/15 15:24:05 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_input
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals;
}	t_input;

typedef struct s_table
{
	struct s_input	input;
	struct timeval	current;
	int				start;
	int				id;
	pid_t			pid;
	pthread_t		guillotine;
	bool			end;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	bool			im_dead;
	pthread_t		think;
	int				nb_eat;
	int				last_meal;
	int				last_sleep;
	sem_t			*printf;
	sem_t			*dessert;
	sem_t			*check_end;
	sem_t			*forks;
	sem_t			*lock_think;
}	t_table;

int		ft_atoi(char *str);
bool	fail_to(bool v);
bool	wrong_number_of_arguments(int argc);
int		time_ms(struct timeval current);
bool	initialise(t_table *table, int argc, char **argv);
void	close_semaphore(t_table *table);
void	destroy_semaphore(void);
void	clear_table(t_table *table);
bool	start_dinner(t_table *table);
bool	dinner_still_going(t_table *table);
bool	create_philosophers(t_table *table);
void	*wait_death(void *arg);
void	philosopher_dies_from_starvation(t_table *table);
void	end_simulation(t_table *table);
void	go_eat(t_table *table);
void	go_sleep(t_table *table);
void	go_think(t_table *table);
void	printf_time(t_table *table, char *s);

#endif