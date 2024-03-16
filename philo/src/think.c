/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:02:31 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/11 17:04:48 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	am_i_dead(t_philo *philo);

void	think(t_philo *philo)
{
	if (fork_available(philo->right_fork))
		take_fork(philo->right_fork, philo, RIGHT);
	else
		pthread_mutex_unlock(&philo->right_fork->mutex);
	if (fork_available(philo->left_fork))
		take_fork(philo->left_fork, philo, LEFT);
	else
		pthread_mutex_unlock(&philo->left_fork->mutex);
	if (philo->has_left_fork && philo->has_right_fork)
	{
		am_i_dead(philo);
		printf_time(philo, "\033[0;34mis eating\033[0m");
		philo->is_thinking = false;
		philo->is_eating = true;
	}
	else
	{
		gettimeofday(&philo->current, NULL);
		if (time_ms(philo->current) - philo->last_meal > \
			philo->table->input.time_to_die)
			philosopher_dies_from_starvation(philo);
		else
			usleep(400);
	}
}

static void	am_i_dead(t_philo *philo)
{
	gettimeofday(&philo->current, NULL);
	if (time_ms(philo->current) - philo->last_meal > \
	philo->table->input.time_to_die)
		philosopher_dies_from_starvation(philo);
}
