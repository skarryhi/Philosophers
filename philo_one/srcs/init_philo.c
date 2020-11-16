/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:42:41 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 12:15:47 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		init_one_philo(t_philo *philo, t_table *table, int nmb)
{
	philo->id = nmb;
	philo->die = 0;
	philo->table = table;
	philo->count_eat = table->count_eat;
	philo->birth = get_time();
	philo->last_meal = philo->birth;
}

void		init_philo(t_table table)
{
	t_philo		philo[table.philo];
	pthread_t	thread[table.philo];
	int			i;

	i = -1;
	while (++i < table.philo)
	{
		init_one_philo(&philo[i], &table, i);
		// pthread_create(&thread[i], NULL, simulation, &philo[i]);
	}
	thread[0] += 0;
}