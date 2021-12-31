/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_mng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 23:56:33 by dchonvil          #+#    #+#             */
/*   Updated: 2021/12/21 23:56:37 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_list	*ft_lstnew(t_philo *philo)
{
    t_list	*box;

    box = malloc(sizeof(t_list));
    if (!box)
    {
        ft_puterr(ALLOCATION);
        return (NULL);
    }
    box->s = philo;
    box->p = NULL;
    box->n = NULL;
    return (box);
}

t_list	*ft_lstmap(t_list *l, t_philo *(*f)(t_tbl *, int), t_tbl *t, int c)
{
    t_list	*box;
    t_list	*final;

    if (!l)
        return (NULL);
    box = l;
    final = ft_lstnew((*f)(t, c));
    if (!final)
        return (NULL);
    ft_lstadd_back(&box, final);
    return (l);
}

void    ft_link_lst(t_list *philos)
{
    t_list *p_philo;

    p_philo = philos;
    p_philo = ft_lstlast(p_philo);
    philos->p = p_philo;
    p_philo->n = philos;
}

void	ft_lstadd_back(t_list **alst, t_list *lst)
{
    t_list	*box;
    t_list	*tmp;

    box = *alst;
    if (!box)
    {
        box = lst;
        return ;
    }
    while (box->n != NULL)
    {
        tmp = box;
        box = box->n;
        box->p = tmp;
    }
    box->n = lst;
}

void	ft_lstclear(t_list **alst, int s)
{
    int c;
    t_list	*box;

    if (!*alst)
        return ;
    c = 0;
    while (c < s)
    {
        box = *alst;
        *alst = box->n;
        if (box->s->f)
        {
            pthread_mutex_destroy(box->s->f);
            free(box->s->f);
        }
        if (box->s->id)
            free(box->s->id);
        if (box->s)
            free(box->s);
        free(box);
        c++;
    }
    *alst = NULL;
}