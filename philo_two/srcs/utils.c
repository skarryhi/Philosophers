/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:03:36 by skarry            #+#    #+#             */
/*   Updated: 2020/11/16 19:41:49 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t		ft_strlen(const char *str)
{
	size_t c;

	c = 0;
	if (str)
		while (str[c])
			c++;
	return (c);
}

void		ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

char		*ft_itoa(int n)
{
	char	*str;
	int		ren;
	int		len;

	len = 0;
	ren = n;
	if (n == 0)
	{
		str = (char*)malloc(2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	if (!((str = (char*)malloc(sizeof(char) * (len + 1)))))
		return (0);
	str[len--] = '\0';
	while (ren != 0)
	{
		str[len--] = ren % 10 + '0';
		ren /= 10;
	}
	return (str);
}

void		str_constr(t_philo *philo, char *str)
{
	char	res[100];
	char	*s1;
	char	*s2;
	int		i;
	int		i2;

	s1 = ft_itoa(get_time() - philo->birth);
	s2 = ft_itoa(philo->id + 1);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = ' ';
	free(s1);
	i2 = -1;
	while (s2[++i2])
		res[i++] = s2[i2];
	res[i++] = ' ';
	free(s2);
	i2 = -1;
	while (str[++i2])
		res[i++] = str[i2];
	res[i++] = '\n';
	res[i] = '\0';
	ft_putstr(res);
}

void		ft_print(t_philo *philo, char *str)
{
	sem_wait(philo->table->sem_print);
	if (philo->table->die && philo->table->print_die)
	{
		sem_post(philo->table->sem_print);
		return ;
	}
	str_constr(philo, str);
	sem_post(philo->table->sem_print);
}
