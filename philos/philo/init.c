/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:43:04 by dchonvil          #+#    #+#             */
/*   Updated: 2021/12/23 20:43:09 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int    tbl_init(char **av, t_tbl *t)
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

t_list *philo_init(char **av, t_tbl *t)
{
    int c;
    t_list *philos;

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

int fork_init(t_list *philos)
{
    int c;
    t_list	*box;

    c = 0;
    box = philos;
    while (c < philos->s->t->p)
    {
        box->s->f = malloc(sizeof(pthread_mutex_t));
        if (!box->s->f)
            return (0);
        if (pthread_mutex_init(box->s->f, NULL))
        {
            printf("%s", MU_KO);
            return (0);
        }
        c++;
        box = box->n;
    }
    return (1);
}

void *meet_philo(void *elem)
{
    t_list *philo;

    philo = (t_list *)elem;
    if (philo->s->t->p > 1)
    {
        while (!philo->s->t->end)
        {
            if (!e_move(philo))
                return (elem);
            ft_move(philo, 'S');
        }
    }
    else
        one_philo(philo);
    return (elem);
}
