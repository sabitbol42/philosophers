/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:18:53 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/15 15:24:37 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philosophers(t_table *table)
{
	int		status;

	table->pid = 1;
	gettimeofday(&table->current, NULL);
	table->start = time_ms(table->current);
	while (++table->id <= table->input.nb_philo)
	{
		if (table->pid != 0)
			table->pid = fork();
		if (table->pid == -1)
		{
			while (table->id-- > 0)
				sem_post(table->dessert);
			while (waitpid(-1, &status, 0) > 0)
				;
			write(2, "Error while creating philosophers\n", 34);
			clear_table(table);
			return (true);
		}
		else if (table->pid == 0)
			break ;
	}
	return (false);
}

void	*wait_death(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	sem_wait(table->dessert);
	sem_wait(table->check_end);
	sem_wait(table->printf);
	table->end = true;
	sem_post(table->printf);
	sem_post(table->check_end);
	i = 0;
	while (i++ < table->input.nb_philo)
		sem_post(table->forks);
	i = 0;
	while (i++ < table->input.nb_philo)
		sem_post(table->dessert);
	return (NULL);
}

void	philosopher_dies_from_starvation(t_table *table)
{
	int	i;

	i = 0;
	while (i++ < table->input.nb_philo)
		sem_post(table->forks);
	pthread_join(table->think, NULL);
	sem_post(table->dessert);
	pthread_join(table->guillotine, NULL);
	table->im_dead = true;
	end_simulation(table);
}
