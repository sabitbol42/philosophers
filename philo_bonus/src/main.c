/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:53:59 by sabitbol          #+#    #+#             */
/*   Updated: 2024/03/14 10:24:48 by sabitbol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (wrong_number_of_arguments(argc))
		return (1);
	if (fail_to(initialise(&table, argc, argv)))
		return (2);
	if (fail_to(start_dinner(&table)))
		return (3);
	clear_table(&table);
	return (0);
}
