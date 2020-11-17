/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:42:41 by skarry            #+#    #+#             */
/*   Updated: 2020/11/17 14:23:36 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		init_one_philo(t_philo *philo, t_table *table, int nmb)
{
	philo->id = nmb;
	philo->table = table;
	philo->count_eat = table->count_eat;
}

void		end_of_eat(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->philo)
		sem_wait(table->end_of_eat);
	sem_post(table->exit);
}

void		sem_closes(t_table *table)
{
	sem_close(table->sem_time);
	sem_close(table->sem_die);
	sem_close(table->sem_print);
	sem_close(table->sem_fork);
	sem_close(table->waiter);
	sem_close(table->exit);
	sem_close(table->end_of_eat);
}

void		init_philo(t_table *table)
{
	t_philo		philo[table->philo];
	pid_t		pid[table->philo + 1];
	int			i;

	i = -1;
	while (++i < table->philo)
	{
		init_one_philo(&philo[i], table, i);
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		else if (pid[i] == 0)
			simulation((void*)&philo[i]);
	}
	pid[i] = fork();
	if (pid[i] < 0)
		exit(1);
	else if (pid[i] == 0)
		end_of_eat(table);
	sem_wait(table->exit);
	i = -1;
	while (++i < table->philo)
		kill(pid[i], SIGKILL);
	sem_closes(table);
}
