/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:29:02 by dchonvil          #+#    #+#             */
/*   Updated: 2022/01/06 00:33:57 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (2048);
	return (0);
}

int	check_numarg(int ac, char **av)
{
	int	c;
	int	i;

	c = 1;
	while (c < ac)
	{
		i = 0;
		while (av[c][i])
		{
			if (!ft_isdigit(av[c][i]))
			{
				ft_puterr(ISN_NUM);
				printf("%s", SUSAGE);
				return (0);
			}
			i++;
		}
		c++;
	}
	return (1);
}

int	check_sarg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		if (ac < 5)
			ft_puterr("Too few arguments.\n");
		else
			ft_puterr("Too many arguments.\n");
		printf("%s", SUSAGE);
		return (0);
	}
	if (!check_numarg(ac, av))
		return (0);
	return (1);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->n != NULL)
		lst = lst->n;
	return (lst);
}
