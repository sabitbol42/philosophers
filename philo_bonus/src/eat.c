/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:32:41 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 18:01:01 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	go_to_sleep(t_table *table);

void	go_eat(t_table *table)
{
	if (table->input.time_to_die < table->input.time_to_eat)
	{
		while (time_ms(table->current) - table->last_meal < \
		table->input.time_to_die)
			gettimeofday(&table->current, NULL);
		philosopher_dies_from_starvation(table);
	}
	else
	{
		table->last_meal = time_ms(table->current);
		while (time_ms(table->current) - table->last_meal < \
		table->input.time_to_eat)
		{
			if (time_ms(table->current) - table->last_meal \
			- table->input.time_to_die < -1)
				usleep(999);
			if (!dinner_still_going(table))
				end_simulation(table);
			gettimeofday(&table->current, NULL);
		}
		go_to_sleep(table);
	}
	table->is_eating = false;
}

static void	go_to_sleep(t_table *table)
{
	table->is_sleeping = true;
	printf_time(table, "\033[0;35mis sleeping\033[0m");
	table->last_sleep = time_ms(table->current);
	sem_post(table->forks);
	sem_post(table->forks);
	table->nb_eat++;
}
