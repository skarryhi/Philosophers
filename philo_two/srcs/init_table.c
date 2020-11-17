/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:01:42 by skarry            #+#    #+#             */
/*   Updated: 2020/11/17 14:17:21 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		my_atoi(const char *str)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while ((*str >= '0' && *str <= '9') && res > -1)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (-1);
	if (res < 1)
		return (-1);
	return (res);
}

void	init_sem(t_table *table)
{
	sem_unlink("sem_time");
	sem_unlink("sem_die");
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	sem_unlink("waiter");
	table->sem_time = sem_open("sem_time", O_CREAT, 0660, 1);
	table->sem_die = sem_open("sem_die", O_CREAT, 0660, 1);
	table->sem_print = sem_open("sem_print", O_CREAT, 0660, 1);
	table->sem_fork = sem_open("sem_fork", O_CREAT, 0660, table->philo);
	table->waiter = sem_open("waiter", O_CREAT, 0660, 1);
}

int		init_table(t_table *table, int ac, char **av)
{
	table->philo = my_atoi(av[1]);
	table->t2die = my_atoi(av[2]);
	table->t2eat = my_atoi(av[3]);
	table->t2sleep = my_atoi(av[4]);
	if (ac == 6)
	{
		table->count_eat = my_atoi(av[5]);
		if (table->count_eat == -1)
			return (1);
	}
	else
		table->count_eat = -1;
	if (table->philo == -1 || table->t2die == -1 ||
		table->t2eat == -1 || table->t2sleep == -1)
		return (1);
	table->die = 0;
	table->print_die = 0;
	init_sem(table);
	init_philo(table);
	return (0);
}

int		put_table(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr(BOLD);
		ft_putstr("Wrong number of arguments\n");
		return (1);
	}
	if (init_table(table, ac, av))
	{
		ft_putstr(BOLD);
		ft_putstr("Invalid arguments\n");
		return (1);
	}
	return (0);
}
