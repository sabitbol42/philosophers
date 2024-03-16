/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:21 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/11 21:19:37 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_die(t_philo *philo);

void	philo_sleep(t_philo *philo)
{
	if (philo->table->input.time_to_die < \
	philo->table->input.time_to_eat + philo->table->input.time_to_sleep)
		wait_to_die(philo);
	else
	{
		while (time_ms(philo->current) - philo->last_sleep < \
		philo->table->input.time_to_sleep)
		{
			if (time_ms(philo->current) - philo->last_sleep - \
			philo->table->input.time_to_sleep < -1)
				usleep(900);
			gettimeofday(&philo->current, NULL);
			if (a_philosopher_is_dead(philo->table))
			{
				philo->is_sleeping = false;
				philo->is_alive = false;
				return ;
			}
		}
		printf_time(philo, "\033[0;32mis thinking\033[0m");
		philo->is_thinking = true;
	}
	philo->is_sleeping = false;
}

static void	wait_to_die(t_philo *philo)
{
	while (time_ms(philo->current) - philo->last_meal \
	< philo->table->input.time_to_die)
		gettimeofday(&philo->current, NULL);
	philosopher_dies_from_starvation(philo);
}
