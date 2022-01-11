/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:31:49 by dchonvil          #+#    #+#             */
/*   Updated: 2022/01/06 00:41:02 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

t_philo	*get_philo(t_tbl *t, int c)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		ft_puterr(ALLOCATION);
		return (NULL);
	}
	philo->t = t;
	philo->e = 0;
	philo->le = 0;
	philo->r = c + 1;
	philo->p_id = -1;
	philo->id = NULL;
	philo->p_crea = 0;
	return (philo);
}

int	get_pthrd(t_list *philos)
{
	int		c;
	t_list	*box;

	c = 0;
	box = philos;
	while (c < philos->s->t->p)
	{
		box->s->id = malloc(sizeof(pthread_t));
		if (!box->s->id)
		{
			ft_puterr(ALLOCATION);
			return (0);
		}
		c++;
		box = box->n;
	}
	return (1);
}

static long long int	treatment(char *box, int t, long long int n)
{
	int	i;
	int	m;

	i = 0;
	m = 1;
	while (box[i] != '\0')
		i++;
	i -= 1;
	while (i >= 0)
	{
		n += (box[i] - 48) * m;
		m *= 10;
		i--;
	}
	if ((t % 2) == 1)
		n = n - (2 * n);
	return (n);
}

long long int	extractor(const char *str, int c, int i)
{
	int				j;
	char			*box;
	long long int	n;

	j = 0;
	box = malloc(sizeof(char) * 20);
	if (!box)
		return (0);
	while ((str[c] > 47 && str[c] < 58))
	{
		if (j > 18)
			return (0);
		box[j] = str[c];
		c++;
		j++;
	}
	box[j] = '\0';
	n = treatment(box, i, 0);
	free(box);
	return (n);
}

long long int	ft_atoi(const char *str)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[c] == '\t' || str[c] == '\n' || str[c] == '\v'
		|| str[c] == '\f' || str[c] == '\r' || str[c] == ' ')
		c++;
	if (!(str[c] == '+' || str[c] == '-' || (str[c] > 47 && str[c] < 58)))
		return (0);
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			i++;
		c++;
	}
	if (str[c] < 48 || str[c] > 57)
		return (0);
	return (extractor(str, c, i));
}
