/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:37:26 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/10 16:09:01 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_input(t_table *table, int argc, char **argv);
static bool	allocate_table(t_table *table);
static bool	init_mutex(t_table *table);
static void	set_table(t_table *table);

bool	initialise(t_table *table, int argc, char **argv)
{
	memset(table, 0, sizeof(t_table));
	if (fail_to(get_input(table, argc, argv)))
		return (true);
	if (fail_to(allocate_table(table)))
	{
		write(2, "Allocation failed\n", 18);
		clear_table(table);
		return (true);
	}
	if (fail_to(init_mutex(table)))
	{
		write(2, "Fail to init mutex\n", 19);
		clear_table(table);
		return (true);
	}
	set_table(table);
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

static bool	allocate_table(t_table *table)
{
	table->philo = malloc(table->input.nb_philo * sizeof(t_philo));
	if (!table->philo)
		return (true);
	memset(table->philo, 0, table->input.nb_philo * sizeof(t_philo));
	table->forks = malloc(table->input.nb_philo * sizeof(t_fork));
	if (!table->forks)
		return (true);
	memset(table->forks, 0, table->input.nb_philo * sizeof(t_fork));
	return (false);
}

static bool	init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->lock_dessert, NULL))
		return (true);
	if (pthread_mutex_init(&table->lock_printf, NULL))
	{
		pthread_mutex_destroy(&table->lock_dessert);
		return (true);
	}
	i = 0;
	while (i < table->input.nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i].mutex, NULL))
		{
			pthread_mutex_destroy(&table->lock_dessert);
			pthread_mutex_destroy(&table->lock_printf);
			while (i-- != 0)
				pthread_mutex_destroy(&table->forks[i].mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	set_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.nb_philo)
	{
		table->forks[i].available = true;
		table->philo[i].id = i + 1;
		table->philo[i].is_thinking = true;
		table->philo[i].is_alive = true;
		table->philo[i].table = table;
		if (i == table->input.nb_philo - 1)
			table->philo[i].right_fork = &table->forks[0];
		else
			table->philo[i].right_fork = &table->forks[i + 1];
		table->philo[i].left_fork = &table->forks[i];
		i++;
	}
}
