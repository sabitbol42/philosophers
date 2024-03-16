/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:45:00 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/15 15:40:19 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_simulation(t_table *table);

bool	start_dinner(t_table *table)
{
	int	status;
	int	i;

	if (fail_to(create_philosophers(table)))
		return (true);
	if (table->pid != 0)
	{
		i = 0;
		while (i++ <= table->input.nb_philo)
			sem_post(table->printf);
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WEXITSTATUS(status) != 255 && !table->im_dead)
			{
				i = WEXITSTATUS(status);
				table->im_dead = true;
			}
		}
		if (table->im_dead)
			return (gettimeofday(&table->current, NULL), printf("\033[0;31m%7d \
		%3d died\033[0m\n", time_ms(table->current) - table->start, i), false);
	}
	else
		start_simulation(table);
	return (false);
}

static void	start_simulation(t_table *table)
{
	if (pthread_create(&table->guillotine, NULL, &wait_death, table))
	{
		write(2, "Error while creating guillotine\n", 32);
		end_simulation(table);
	}
	sem_wait(table->printf);
	table->last_meal = table->start;
	if (table->id % 2 == 0)
		usleep(50000);
	while (dinner_still_going(table) && (table->nb_eat < \
	table->input.nb_of_meals || table->input.nb_of_meals == -2))
	{
		if (table->is_eating)
			go_eat(table);
		if (table->is_sleeping)
			go_sleep(table);
		if (table->is_thinking)
			go_think(table);
	}
	end_simulation(table);
}

bool	dinner_still_going(t_table *table)
{
	sem_wait(table->check_end);
	if (table->end == true)
	{
		sem_post(table->check_end);
		return (false);
	}
	sem_post(table->check_end);
	return (true);
}

void	end_simulation(t_table *table)
{
	int	i;

	i = 0;
	if (dinner_still_going(table))
	{
		while (i++ < table->input.nb_philo)
		{
			sem_post(table->dessert);
		}
	}
	pthread_join(table->guillotine, NULL);
	i = 0;
	while (i++ < table->input.nb_philo)
	{
		sem_post(table->forks);
	}
	pthread_join(table->think, NULL);
	close_semaphore(table);
	if (table->nb_eat == table->input.nb_of_meals || !table->im_dead)
		exit(-1);
	else
		exit(table->id);
}
