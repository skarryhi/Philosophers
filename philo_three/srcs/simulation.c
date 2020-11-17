/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:39:49 by skarry            #+#    #+#             */
/*   Updated: 2020/11/17 14:07:24 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		sem_death(t_philo *philo)
{
	sem_wait(philo->table->sem_die);
	ft_print((t_philo *)philo, BOLD""RED"died"WHITE, 1);
	sem_post(philo->table->exit);
}

void		*death(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	sem_wait(philo->table->sem_time);
	while ((get_time() - philo->last_meal) <= philo->table->t2die &&
			philo->count_eat != 0)
	{
		sem_post(philo->table->sem_time);
		usleep(10);
		sem_wait(philo->table->sem_time);
	}
	sem_post(philo->table->sem_time);
	if (philo->count_eat == 0)
	{
		sem_post(philo->table->end_of_eat);
		exit(0);
	}
	else
		sem_death(philo);
	return (NULL);
}

void		main_loop(t_philo *philo)
{
	sem_wait(philo->table->waiter);
	sem_wait(philo->table->sem_fork);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE, 0);
	sem_wait(philo->table->sem_fork);
	ft_print((t_philo *)philo, BOLD""GRN"has taken a fork"WHITE, 0);
	sem_post(philo->table->waiter);
	ft_print((t_philo *)philo, BOLD""CYN"is eating"WHITE, 0);
	philo->last_meal = get_time();
	ft_wait(philo->table->t2eat);
	sem_post(philo->table->sem_fork);
	sem_post(philo->table->sem_fork);
	ft_print((t_philo *)philo, BOLD""MAG"is sleeping"WHITE, 0);
	philo->count_eat--;
	ft_wait(philo->table->t2sleep);
	ft_print((t_philo *)philo, BOLD""YEL"is thinking"WHITE, 0);
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
