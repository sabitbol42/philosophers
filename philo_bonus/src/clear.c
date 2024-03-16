/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:30:50 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/12 15:47:11 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_table(t_table *table)
{
	destroy_semaphore();
	close_semaphore(table);
}

void	close_semaphore(t_table *table)
{
	if (table->printf)
		sem_close(table->printf);
	if (table->dessert)
		sem_close(table->dessert);
	if (table->forks)
		sem_close(table->forks);
	if (table->check_end)
		sem_close(table->check_end);
	if (table->lock_think)
		sem_close(table->lock_think);
}

void	destroy_semaphore(void)
{
	sem_unlink("printf");
	sem_unlink("dessert");
	sem_unlink("forks");
	sem_unlink("check_end");
	sem_unlink("lock_think");
}
