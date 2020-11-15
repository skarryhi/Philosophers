/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:42:41 by skarry            #+#    #+#             */
/*   Updated: 2020/11/15 20:16:15 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		init_one_philo(t_philo *philo, t_table *table, int nmb)
{
	philo->id = nmb;
	philo->table = table;
	philo->count_eat = table->count_eat;
}

void		init_philo(t_table table)
{
	t_philo		philo[table.philo];
	int			i;

	i = -1;
	while (++i < table.philo)
	{
		init_one_philo(&philo[i], &table, i);
		pthread_create(&threads[i], NULL, simulation, &philos[i]);
	}
}