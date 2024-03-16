/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:40:05 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/11 17:06:24 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	fork_available(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->available)
		return (true);
	return (false);
}

void	take_fork(t_fork *fork, t_philo *philo, bool hand)
{
	fork->available = false;
	pthread_mutex_unlock(&fork->mutex);
	gettimeofday(&philo->current, NULL);
	printf_time(philo, "\033[0;36mhas taken a fork\033[0m");
	if (hand == LEFT)
		philo->has_left_fork = true;
	else
		philo->has_right_fork = true;
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->right_fork->available = true;
	philo->left_fork->available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->has_right_fork = false;
	philo->has_left_fork = false;
}
