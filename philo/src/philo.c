/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:47:36 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/11 21:00:08 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_diner(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->lock_printf);
	while (i < table->input.nb_philo)
	{
		if (pthread_create(&table->philo[i].thread, \
			NULL, &routine, &table->philo[i]))
		{
			while (i-- != 0)
				pthread_detach(table->philo[i].thread);
			write(2, "Error creating thread\n", 22);
			pthread_mutex_unlock(&table->lock_printf);
			destroy_all_mutex(table);
			clear_table(table);
			return (true);
		}
		i++;
	}
	gettimeofday(&table->philo[0].current, NULL);
	table->start = time_ms(table->philo[0].current);
	pthread_mutex_unlock(&table->lock_printf);
	while (i-- != 0)
		pthread_join(table->philo[i].thread, NULL);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->lock_printf);
	pthread_mutex_unlock(&philo->table->lock_printf);
	philo->last_meal = philo->table->start;
	if (philo->id % 2 == 0)
		usleep(50000);
	while (philo->is_alive && \
	(philo->table->input.nb_of_meals > philo->nb_eat || \
	philo->table->input.nb_of_meals == -2))
	{
		if (philo->is_thinking)
			think(philo);
		if (philo->is_eating)
			eat(philo);
		if (philo->is_sleeping)
			philo_sleep(philo);
		if (a_philosopher_is_dead(philo->table))
			return (0);
	}
	return (0);
}

void	philosopher_dies_from_starvation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock_dessert);
	if (philo->table->dessert == true)
	{
		pthread_mutex_unlock(&philo->table->lock_dessert);
		philo->is_alive = false;
		return ;
	}
	philo->table->dessert = true;
	pthread_mutex_unlock(&philo->table->lock_dessert);
	pthread_mutex_lock(&philo->table->lock_printf);
	gettimeofday(&philo->current, NULL);
	printf("\033[0;31m%7d %3d died\033[0m\n", \
	time_ms(philo->current) - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->lock_printf);
	philo->is_alive = false;
}

bool	a_philosopher_is_dead(t_table *table)
{
	pthread_mutex_lock(&table->lock_dessert);
	if (table->dessert)
	{
		pthread_mutex_unlock(&table->lock_dessert);
		return (true);
	}
	pthread_mutex_unlock(&table->lock_dessert);
	return (false);
}
