/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:42:41 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 18:26:39 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		init_one_philo(t_philo *philo, t_table *table, int nmb)
{
	philo->id = nmb;
	philo->table = table;
	philo->count_eat = table->count_eat;
}

void		init_philo(t_table *table)
{
	t_philo		philo[table->philo];
	pthread_t	thread[table->philo];
	int			i;

	i = -1;
	while (++i < table->philo)
	{
		init_one_philo(&philo[i], table, i);
		pthread_create(&thread[i], NULL, simulation, &philo[i]);
	}
	i = -1;
	while (++i < table->philo)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < table->philo)
		pthread_mutex_destroy(&table->mutx_fork[i]);
	free(table->mutx_fork);
}
