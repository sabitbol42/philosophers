/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:37:26 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 17:26:57 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_input(t_table *table, int argc, char **argv);
static bool	create_semaphore(t_table *table);

bool	initialise(t_table *table, int argc, char **argv)
{
	memset(table, 0, sizeof(t_table));
	if (fail_to(get_input(table, argc, argv)))
		return (true);
	if (fail_to(create_semaphore(table)))
	{
		write(2, "Fail to create semaphore\n", 25);
		clear_table(table);
		return (true);
	}
	table->is_thinking = true;
	return (false);
}

static bool	get_input(t_table *table, int argc, char **argv)
{
	table->input.nb_philo = ft_atoi(argv[1]);
	table->input.time_to_die = ft_atoi(argv[2]);
	table->input.time_to_eat = ft_atoi(argv[3]);
	table->input.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->input.nb_of_meals = ft_atoi(argv[5]);
	else
		table->input.nb_of_meals = -2;
	if (table->input.nb_philo <= 0 || \
		table->input.time_to_die == -1 || \
		table->input.time_to_eat == -1 || \
		table->input.time_to_sleep == -1 || \
		table->input.nb_of_meals == -1)
	{
		write(2, "Wrong input value\n", 18);
		return (true);
	}
	return (false);
}

static bool	create_semaphore(t_table *table)
{
	destroy_semaphore();
	table->printf = sem_open("printf", O_CREAT | O_EXCL, 00700, 0);
	if (table->printf == SEM_FAILED)
		return (true);
	table->dessert = sem_open("dessert", O_CREAT | O_EXCL, 00700, 0);
	if (table->dessert == SEM_FAILED)
		return (true);
	table->check_end = sem_open("check_end", O_CREAT | O_EXCL, 00700, 1);
	if (table->check_end == SEM_FAILED)
		return (true);
	table->forks = sem_open("forks", O_CREAT | O_EXCL, 00700, \
	table->input.nb_philo);
	if (table->forks == SEM_FAILED)
		return (true);
	table->lock_think = sem_open("lock_think", O_CREAT | O_EXCL, 00700, 1);
	if (table->lock_think == SEM_FAILED)
		return (true);
	return (false);
}
