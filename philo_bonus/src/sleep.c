/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:33:30 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 18:01:14 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_table *table)
{
	if (table->input.time_to_die < \
	table->input.time_to_eat + table->input.time_to_sleep)
	{
		while (time_ms(table->current) - table->last_meal < \
		table->input.time_to_die)
			gettimeofday(&table->current, NULL);
		philosopher_dies_from_starvation(table);
	}
	else
	{
		while (time_ms(table->current) - table->last_sleep < \
		table->input.time_to_sleep)
		{
			if (time_ms(table->current) - table->last_sleep - \
			table->input.time_to_sleep < -1)
				usleep(999);
			if (!dinner_still_going(table))
				end_simulation(table);
			gettimeofday(&table->current, NULL);
		}
		table->is_thinking = true;
		printf_time(table, "\033[0;32mis thinking\033[0m");
		usleep(2000);
	}
	table->is_sleeping = false;
}
