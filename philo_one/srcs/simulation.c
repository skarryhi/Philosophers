/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:39:49 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 16:37:13 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*death(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->table->mutx_time);
	while ((get_time() - philo->last_meal) <= philo->table->t2die && philo->count_eat != 0 && philo->table->die == 0)
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
		ft_print((t_philo *)philo, "died");
		pthread_mutex_unlock(&philo->table->mutx_die);
	}
	return (NULL);
}

void		*simulation(void *philos)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)philos;
	philo->birth = get_time();
	philo->last_meal = get_time();
	ft_print((t_philo *)philo, "birth");
	pthread_create(&thread, NULL, death, philo);
	while (philo->count_eat != 0 && !philo->table->die)
	{
		if (philo->id % 2 == 1)
			pthread_mutex_lock(&philo->table->mutx_fork[philo->id]);
		else
		{
			pthread_mutex_lock(&philo->table->mutx_fork[(philo->id + 1) % philo->table->philo]);
		}
		ft_print((t_philo *)philo, "has taken a fork");
		if (philo->id % 2 == 1)
			pthread_mutex_lock(&philo->table->mutx_fork[(philo->id + 1) % philo->table->philo]);
		else
		{
			pthread_mutex_lock(&philo->table->mutx_fork[philo->id]);
		}
		ft_print((t_philo *)philo, "is eating");
		philo->last_meal = get_time();
		ft_wait(philo->table->t2eat);
		pthread_mutex_unlock(&philo->table->mutx_fork[(philo->id + 1) % philo->table->philo]);
		pthread_mutex_unlock(&philo->table->mutx_fork[philo->id]);
		ft_print((t_philo *)philo, "is sleeping");
		philo->count_eat--;
		ft_wait(philo->table->t2sleep);
		ft_print((t_philo *)philo, "is thinking");
	}
	pthread_join(thread, NULL);
	return (NULL);
}