/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 04:07:48 by dchonvil          #+#    #+#             */
/*   Updated: 2021/12/31 19:07:05 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	ft_pthrd_dtch(t_list *philos)
{
	int		c;
	t_list	*box;

	c = 0;
	box = philos;
	while (c < philos->s->t->p)
	{
		if (!pthread_join(*(box)->s->id, NULL))
			pthread_detach(*(box)->s->id);
		c++;
		box = box->n;
	}
}

void	ft_pthrd_join(t_list *philos)
{
	int		c;
	int		r;
	t_list	*box;

	c = 0;
	r = 1;
	box = philos;
	while (c < philos->s->t->p && r)
	{
		if (pthread_join(*(box)->s->id, NULL) || philos->s->t->end)
		{
			ft_pthrd_dtch(philos);
			r = 0;
		}
		c++;
		box = box->n;
	}
	if (philos->s->t->loop == philos->s->t->ne)
		printf("%s", NBM_OK);
}

int	ft_pthrd_start(t_list *philos)
{
	int		c;
	t_list	*box;

	philos->s->t->ts = get_dt();
	box = philos;
	c = 0;
	while (c < philos->s->t->p)
	{
		box->s->le = philos->s->t->ts;
		if (pthread_create(box->s->id, NULL, meet_philo, (void *)box))
		{
			ft_puterr(PTH_KO);
			ft_pthrd_dtch(philos);
			return (0);
		}
		c++;
		box = box->n;
	}
	return (1);
}

void	start_philo(t_list *philos)
{
	if (philos->s->t->ne == 0)
	{
		printf("%s", NBM_OK);
		return ;
	}
	if (!get_pthrd(philos))
		return ;
	ft_link_lst(philos);
	if (!ft_pthrd_start(philos))
		return ;
	ft_pthrd_join(philos);
}

int	main(int ac, char **av)
{
	t_tbl	t;
	t_list	*philos;

	if (!check_sarg(ac, av))
		return (1);
	philos = philo_init(av, &t);
	if (!philos)
		return (1);
	if (!fork_init(philos))
	{
		ft_lstclear(&philos, t.p);
		return (1);
	}
	start_philo(philos);
	ft_lstclear(&philos, t.p);
	return (0);
}
