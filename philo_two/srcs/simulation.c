/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:39:49 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 19:46:52 by skarry           ###   ########.fr       */
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
	sem_wait(philo->table->sem_time);
	while ((get_time() - philo->last_meal) <= philo->table->t2die &&
			philo->count_eat != 0 && philo->table->die == 0)
	{
		sem_post(philo->table->sem_time);
		usleep(10);
		sem_wait(philo->table->sem_time);
	}
	sem_post(philo->table->sem_time);
	if (philo->count_eat == 0)
		return (NULL);
	else
	{
		sem_wait(philo->table->sem_die);
		philo->table->die = 1;
		ft_print((t_philo *)philo, BOLD""RED"died"WHITE);
		++philo->table->print_die;
		sem_post(philo->table->sem_die);
	}
	return (NULL);
}

void		main_loop(t_philo *philo)
{
	sem_wait(philo->table->waiter);
	sem_wait(philo->table->sem_fork);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE);
	sem_wait(philo->table->sem_fork);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE);
	sem_post(philo->table->waiter);
	ft_print((t_philo *)philo, BOLD""CYN"is eating"WHITE);
	philo->last_meal = get_time();
	ft_wait(philo->table->t2eat);
	sem_post(philo->table->sem_fork);
	sem_post(philo->table->sem_fork);
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
