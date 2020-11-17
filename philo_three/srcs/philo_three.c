/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:47:07 by skarry            #+#    #+#             */
/*   Updated: 2020/11/17 14:02:57 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((int)(((current.tv_sec) * 1000) + ((current.tv_usec) / 1000)));
}

void		ft_wait(int time)
{
	int				start;
	int				stop;
	int				diff;

	start = get_time();
	stop = get_time();
	diff = stop - start;
	while (diff < time)
	{
		stop = get_time();
		diff = stop - start;
		usleep(10);
	}
}

int			main(int argc, char **argv)
{
	t_table		table;

	if (put_table(&table, argc, argv))
		return (1);
	return (0);
}
