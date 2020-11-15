/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:48:39 by skarry            #+#    #+#             */
/*   Updated: 2020/11/15 19:39:32 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define WHITE	"\x1B[0m"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define BOLD	"\033[1m"

typedef	struct			s_table
{
	int					philo;
	int					t2die;
	int					t2eat;
	int					t2sleep;
	int					count_eat;
	int					die;
}						t_table;

typedef	struct			s_philo
{
	int					id;
	int					birth;
	int					last_meal;
	int					die;
	t_table				table;
}						t_philo;

int		put_table(t_table *table, int ac, char **av);
void	ft_putstr(char *s);

#endif