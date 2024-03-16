/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:33:45 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 18:00:43 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*wait_forks(void *arg);
static bool	philo_is_thinking(t_table *table);

void	go_think(t_table *table)
{
	if (table->nb_eat == table->input.nb_of_meals)
		return ;
	if (dinner_still_going(table) && \
	pthread_create(&table->think, NULL, wait_forks, table))
	{
		write(2, "Error while thinking\n", 21);
		end_simulation(table);
	}
	while (philo_is_thinking(table))
	{
		gettimeofday(&table->current, NULL);
		if (time_ms(table->current) - table->last_meal > \
		table->input.time_to_die)
			philosopher_dies_from_starvation(table);
		if (!dinner_still_going(table))
			end_simulation(table);
		usleep(499);
	}
	pthread_join(table->think, NULL);
	if (time_ms(table->current) - table->last_meal > \
	table->input.time_to_die)
		philosopher_dies_from_starvation(table);
	table->is_eating = true;
	printf_time(table, "\033[0;34mis eating\033[0m");
}

static bool	philo_is_thinking(t_table *table)
{
	sem_wait(table->lock_think);
	if (table->is_thinking == true)
	{
		sem_post(table->lock_think);
		return (true);
	}
	sem_post(table->lock_think);
	return (false);
}

void	*wait_forks(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	sem_wait(table->forks);
	printf_time(table, "\033[0;36mhas taken a fork\033[0m");
	sem_wait(table->forks);
	printf_time(table, "\033[0;36mhas taken a fork\033[0m");
	sem_wait(table->lock_think);
	table->is_thinking = false;
	sem_post(table->lock_think);
	return (NULL);
}
