/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 07:27:12 by dchonvil          #+#    #+#             */
/*   Updated: 2021/12/31 20:05:45 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	one_philo(t_list *philo)
{
	e_move(philo);
	while ((get_dt() - philo->s->t->ts) < philo->s->t->d)
		usleep(1);
	ft_timer(DI, philo->s->r);
	philo->s->t->end = 1;
}

void	nbe_check(t_list *philo)
{
	philo->s->t->c_eat += 1;
	if (philo->s->t->c_eat >= philo->s->t->p)
	{
		philo->s->t->c_eat = 0;
		philo->s->t->loop += 1;
	}
	if (philo->s->t->loop == philo->s->t->ne)
		philo->s->t->end = 1;
	philo->s->le = get_dt();
}

void	ft_move(t_list *philo, char move)
{
	unsigned long long int	t;

	t = get_dt();
	if (move == 'E')
	{
		ft_timer(TF, philo->s->r);
		ft_timer(IE, philo->s->r);
		while ((get_dt() - t) < philo->s->t->e)
			usleep(1);
		nbe_check(philo);
	}
	else
	{
		ft_timer(IS, philo->s->r);
		while ((get_dt() - t) < philo->s->t->s)
			usleep(1);
		ft_timer(IT, philo->s->r);
	}
}

int	e_move(t_list *philo)
{
	pthread_mutex_lock(philo->s->f);
	ft_timer(TF, philo->s->r);
	if (philo->s->t->p > 1)
	{
		if ((get_dt() - philo->s->le) > philo->s->t->d)
		{
			ft_timer(DI, philo->s->r);
			pthread_mutex_unlock(philo->s->f);
			philo->s->t->end = 1;
			return (0);
		}
		pthread_mutex_lock(philo->n->s->f);
		ft_move(philo, 'E');
		pthread_mutex_unlock(philo->n->s->f);
	}
	pthread_mutex_unlock(philo->s->f);
	return (1);
}
