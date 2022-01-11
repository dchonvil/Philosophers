/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:18:12 by dchonvil          #+#    #+#             */
/*   Updated: 2022/01/06 00:51:29 by dchonvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define DI "died\n"
# define ERROR "Error\n"
# define IE "is eating\n"
# define IS "is sleeping\n"
# define IT "is thinking\n"
# define TF "has taken a fork\n"
# define TDI "Insufficient time to die.\n"
# define NO_P "Zero philosopher create.\n"
# define NBM_OK "Number of meals reached.\n"
# define MU_KO "The mutex could not be created.\n"
# define PTH_KO "The thread could not be created.\n"
# define PID_KO "The process could not be created.\n"
# define SEM_KO "The semaphore could not be created.\n"
# define ISN_NUM "One of the arguments is not a number.\n"
# define NEG_VAL "One of the timers has a negative value.\n"
# define ALLOCATION "The program could not allocate the necessary memory.\n"
# define SUSAGE "Usage: ./philo NbPhilo TimeDie TimeEat TimeSleep (NbMustEat)\n"

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_tbl
{
	int						p;
	int						end;
	int						c_eat;
	int						af;
	sem_t					*f;
	unsigned long long int	d;
	unsigned long long int	e;
	unsigned long long int	s;
	unsigned long long int	ne;
	unsigned long long int	ts;
	unsigned long long int	loop;
}	t_tbl;

typedef struct s_philo
{
	int						e;
	int						r;
	int						p_crea;
	pid_t					p_id;
	pthread_t				*id;
	t_tbl					*t;
	unsigned long long int	le;
}	t_philo;

typedef struct s_list
{
	t_philo			*s;
	struct s_list	*n;
	struct s_list	*p;
}	t_list;

unsigned long long int	get_dt(void);
void					ft_puterr(char *e);
int						fork_init(t_tbl *t);
int						e_move(t_list *philo);
void					*meet_philo(void *elem);
void					nbe_check(t_list *philo);
void					one_philo(t_list *philo);
void					ft_timer(char *s, int r);
long long int			ft_atoi(const char *str);
t_list					*ft_lstlast(t_list *lst);
int						get_pthrd(t_list *philos);
t_list					*ft_lstnew(t_philo *philo);
void					ft_link_lst(t_list *philos);
t_philo					*get_philo(t_tbl *t, int c);
int						check_sarg(int ac, char **av);
t_list					*philo_init(char **av, t_tbl *t);
void					ft_lstclear(t_list **alst, int s);
void					ft_check(t_tbl *t, t_list *philo);
void					ft_move(t_list *philo, char move);
void					ft_lstadd_back(t_list **alst, t_list *lst);
t_list					*ft_lstmap(t_list *l, t_philo *(*f)(t_tbl *, int),
							t_tbl *t, int c);

#endif
