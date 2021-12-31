/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 03:54:48 by dchonvil          #+#    #+#             */
/*   Updated: 2021/12/21 03:54:52 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_check(t_tbl *t, t_list *philos)
{
    int c;
    t_list	*box;

    printf("\nTable\n");
    printf("TStart : %lld\n", t->ts);
    printf("NbPhilo : %d\n", t->p);
    printf("TEat : %lld\n", t->e);
    printf("TSleep : %lld\n", t->s);
    printf("TDie : %lld\n", t->d);
    printf("NbEat : %lld\n\n", t->ne);
    printf("\nPhiloTab :\n");
    if (!philos)
    {
        printf("NO Tab\n");
        return ;
    }
    c = 0;
    box = philos;
    while (c < t->p)
    {
        printf("Philo_%d\n", box->s->r);
        printf("LastEat : %lld\n", box->s->le);
        box = box->n;
        c++;
    }
}

unsigned long long int get_dt(void)
{
    static struct timeval	time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_timer(char *s, int r)
{
    printf("%lld %d %s\n", get_dt(), r, s);
}

void	ft_puterr(char *e)
{
    printf("%s", ERROR);
    printf("%s", e);
}