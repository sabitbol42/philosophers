/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:32:26 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 17:59:07 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	nb;

	nb = 0;
	if (!*str)
		return (-1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nb = (nb * 10) + (*str - '0');
		if (nb < 0)
			return (-1);
		str++;
	}
	return (nb);
}

bool	fail_to(bool v)
{
	return (v);
}

bool	wrong_number_of_arguments(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (true);
	}
	return (false);
}

int	time_ms(struct timeval current)
{
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	printf_time(t_table *table, char *s)
{
	sem_wait(table->check_end);
	if (table->end)
	{
		sem_post(table->check_end);
		return ;
	}
	gettimeofday(&table->current, NULL);
	printf("\033[38;5;218m%7d\033[33m %3d\033[0m %s\n", \
	time_ms(table->current) - table->start, table->id, s);
	sem_post(table->check_end);
}
