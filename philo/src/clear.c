/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:06:31 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/08 18:44:11 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_table(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->forks)
		free(table->forks);
}

void	destroy_all_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->lock_dessert);
	pthread_mutex_destroy(&table->lock_printf);
	i = 0;
	while (i < table->input.nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
}
