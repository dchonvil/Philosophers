/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:30:49 by dchonvil          #+#    #+#             */
/*   Updated: 2022/01/06 00:37:12 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include "philo_bonus.h"

void	one_philo(t_list *philo)
{
	e_move(philo);
	while ((get_dt() - philo->s->t->ts) < philo->s->t->d)
		usleep(1);
	if (philo->s->p_id != 0)
		ft_timer(DI, philo->s->r);
	philo->s->t->end = 1;
	kill(philo->s->p_id, SIGTERM);
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
		if (philo->s->p_id != 0)
			ft_timer(TF, philo->s->r);
		if (philo->s->p_id != 0)
			ft_timer(IE, philo->s->r);
		while ((get_dt() - t) < philo->s->t->e)
			usleep(1);
		nbe_check(philo);
	}
	else
	{
		if (philo->s->p_id != 0)
			ft_timer(IS, philo->s->r);
		while ((get_dt() - t) < philo->s->t->s)
			usleep(1);
		if (philo->s->p_id != 0)
			ft_timer(IT, philo->s->r);
	}
}

int	e_move_treat(t_list *philo)
{
	if (philo->s->t->af < 1)
	{
		sem_post(philo->s->t->f);
		philo->s->t->af += 1;
		return (2);
	}
	sem_wait(philo->s->t->f);
	philo->s->t->af -= 1;
	if ((get_dt() - philo->s->le) > philo->s->t->d)
	{
		if (philo->s->p_id != 0)
			ft_timer(DI, philo->s->r);
		sem_post(philo->s->t->f);
		sem_post(philo->s->t->f);
		philo->s->t->af += 2;
		philo->s->t->end = 1;
		kill(philo->s->p_id, SIGTERM);
		return (0);
	}
	ft_move(philo, 'E');
	sem_post(philo->s->t->f);
	philo->s->t->af += 1;
	return (1);
}

int	e_move(t_list *philo)
{
	int	c;

	if (philo->s->t->af < 2)
		return (2);
	sem_wait(philo->s->t->f);
	philo->s->t->af -= 1;
	if (philo->s->p_id != 0)
		ft_timer(TF, philo->s->r);
	if (philo->s->t->p > 1)
	{
		c = e_move_treat(philo);
		if (c == 0 || c == 2)
			return (c);
	}
	sem_post(philo->s->t->f);
	philo->s->t->af += 1;
	return (1);
}
