/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:39:49 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 18:55:42 by skarry           ###   ########.fr       */
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

void		*death(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->table->mutx_time);
	while ((get_time() - philo->last_meal) <= philo->table->t2die &&
			philo->count_eat != 0 && philo->table->die == 0)
	{
		pthread_mutex_unlock(&philo->table->mutx_time);
		usleep(10);
		pthread_mutex_lock(&philo->table->mutx_time);
	}
	pthread_mutex_unlock(&philo->table->mutx_time);
	if (philo->count_eat == 0)
		return (NULL);
	else
	{
		pthread_mutex_lock(&philo->table->mutx_die);
		philo->table->die = 1;
		ft_print((t_philo *)philo, BOLD""RED"died"WHITE);
		++philo->table->print_die;
		pthread_mutex_unlock(&philo->table->mutx_die);
	}
	return (NULL);
}

void		main_loop(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->table->mutx_fork[philo->id]);
	else
		pthread_mutex_lock(&philo->table->mutx_fork[(philo->id + 1)
											% philo->table->philo]);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->table->mutx_fork[(philo->id + 1)
											% philo->table->philo]);
	else
		pthread_mutex_lock(&philo->table->mutx_fork[philo->id]);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE);
	ft_print((t_philo *)philo, BOLD""CYN"is eating"WHITE);
	philo->last_meal = get_time();
	ft_wait(philo->table->t2eat);
	pthread_mutex_unlock(&philo->table->mutx_fork[(philo->id + 1)
											% philo->table->philo]);
	pthread_mutex_unlock(&philo->table->mutx_fork[philo->id]);
	ft_print((t_philo *)philo, BOLD""MAG"is sleeping"WHITE);
	philo->count_eat--;
	ft_wait(philo->table->t2sleep);
	ft_print((t_philo *)philo, BOLD""YEL"is thinking"WHITE);
}

void		*simulation(void *philos)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)philos;
	philo->birth = get_time();
	philo->last_meal = get_time();
	pthread_create(&thread, NULL, death, philo);
	while (philo->count_eat != 0 && !philo->table->die)
		main_loop(philo);
	pthread_join(thread, NULL);
	return (NULL);
}
