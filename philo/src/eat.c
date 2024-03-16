/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:05:54 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/12 13:19:41 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_dying(t_philo *philo);
static void	go_to_sleep(t_philo *philo);

void	eat(t_philo *philo)
{
	if (philo->table->input.time_to_die < philo->table->input.time_to_eat)
		philo_is_dying(philo);
	else
	{
		philo->last_meal = time_ms(philo->current);
		while (time_ms(philo->current) - philo->last_meal < \
		philo->table->input.time_to_eat)
		{
			if (time_ms(philo->current) - philo->last_meal - \
			philo->table->input.time_to_eat < -1)
				usleep(900);
			if (a_philosopher_is_dead(philo->table))
			{
				philo->is_eating = false;
				philo->is_alive = false;
				return ;
			}
			gettimeofday(&philo->current, NULL);
		}
		go_to_sleep(philo);
	}
	philo->is_eating = false;
}

static void	philo_is_dying(t_philo *philo)
{
	while (time_ms(philo->current) - philo->last_meal < \
	philo->table->input.time_to_die)
		gettimeofday(&philo->current, NULL);
	philosopher_dies_from_starvation(philo);
}

static void	go_to_sleep(t_philo *philo)
{
	printf_time(philo, "\033[0;35mis sleeping\033[0m");
	philo->is_sleeping = true;
	philo->last_sleep = time_ms(philo->current);
	put_forks(philo);
	philo->nb_eat++;
}
