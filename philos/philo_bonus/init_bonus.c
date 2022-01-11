/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:29:26 by dchonvil          #+#    #+#             */
/*   Updated: 2022/01/06 00:34:56 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "philo_bonus.h"

int	tbl_init(char **av, t_tbl *t)
{
	t->p = ft_atoi(av[1]);
	if (t->p < 1 || t->p > 30000)
	{
		printf("%s", NO_P);
		return (0);
	}
	t->d = ft_atoi(av[2]);
	t->e = ft_atoi(av[3]);
	t->s = ft_atoi(av[4]);
	if (t->d < 0 || t->e < 0 || t->s < 0)
	{
		printf("%s", NEG_VAL);
		return (0);
	}
	if (av[5])
		t->ne = ft_atoi(av[5]);
	else
		t->ne = -1;
	t->end = 0;
	t->loop = 0;
	t->c_eat = 0;
	return (1);
}

t_list	*philo_init(char **av, t_tbl *t)
{
	int		c;
	t_list	*philos;

	if (!tbl_init(av, t))
		return (NULL);
	philos = ft_lstnew(get_philo(t, 0));
	if (!philos)
		return (NULL);
	c = 1;
	while (c < t->p)
	{
		philos = ft_lstmap(philos, &get_philo, t, c);
		if (!philos)
		{
			ft_lstclear(&philos, t->p);
			return (NULL);
		}
		c++;
	}
	return (philos);
}

int	fork_init(t_tbl *t)
{
	t->f = sem_open("Forks", O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, t->p);
	if (t->f == SEM_FAILED)
	{
		ft_puterr(SEM_KO);
		return (0);
	}
	t->af = t->p;
	return (1);
}

int	ft_forker(t_list *philo)
{
	if (philo->s->p_crea)
		return (1);
	philo->s->p_id = fork();
	if (philo->s->p_id == -1)
	{
		ft_puterr(PID_KO);
		return (0);
	}
	philo->s->p_crea = 1;
	return (1);
}

void	*meet_philo(void *elem)
{
	int		c;
	t_list	*philo;

	philo = (t_list *)elem;
	if (!ft_forker(philo))
		return (elem);
	if (philo->s->t->p > 1)
	{
		while (!philo->s->t->end)
		{
			c = e_move(philo);
			if (!c)
				return (elem);
			else if (c == 1)
				ft_move(philo, 'S');
		}
	}
	else
		one_philo(philo);
	return (elem);
}
