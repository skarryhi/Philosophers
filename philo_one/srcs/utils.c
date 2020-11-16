/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:03:36 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 16:37:44 by skarry           ###   ########.fr       */
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
void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void	ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + '0');
	}
	else
		ft_putchar(n + '0');
}


void		ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->mutx_print);
	if (philo->table->die == 1 && philo->table->print_die == 1)
	{
		pthread_mutex_unlock(&philo->table->mutx_print);
		return ;
	}
	if (philo->table->die == 1 && philo->table->print_die == 0)
		++philo->table->print_die;
	ft_putnbr(get_time() - philo->birth);
	ft_putchar(' ');
	ft_putnbr(philo->id + 1);
	ft_putchar(' ');
	ft_putstr(str);
	ft_putchar('\n');
	pthread_mutex_unlock(&philo->table->mutx_print);
}