/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:01:42 by skarry            #+#    #+#             */
/*   Updated: 2020/11/15 19:22:56 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr(char *s)
{
	int		i;

	if (s)
	{
		i = 0;
		while (s[i])
			write(1, &s[i++], 1);
	}
}

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
	if (res < 1)
		return (-1);
	return (res);
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
	return(0);
}

int		put_table(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr(BOLD);
		ft_putstr("Wrong number of arguments\n");
		return(1);
	}
	if (init_table(table, ac, av))
	{
		ft_putstr(BOLD);
		ft_putstr("Invalid arguments\n");
		return(1);
	}
	av += 0;
	table += 0;
	return (0);
}