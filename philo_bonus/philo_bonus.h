/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:49:57 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 18:50:42 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int					id;
	int					eat_cnt;
	long long			last_eat;
	pid_t				processes_id;
	pthread_t			tread;
	struct s_rules		*rules;
}				t_philo;

typedef struct s_rules
{
	int					numbers;
	int					die;
	int					eat;
	int					sleep;
	int					n_must_eat;
	long long			start_time;
	int					dieded;
	sem_t				*forks;
	sem_t				*write;
	sem_t				*check_eat;
	t_philo				philo[200];
}				t_rules;

size_t		ft_strlen(const char *s);
int			ft_exit(int error_num);
int			ft_atoi(const char *str);
int			start(t_rules *rules, int argc, char **argv);
long long	get_time(void);
void		message(t_rules *rules, int id, char *message);
void		waiting(long long time, t_rules *rules);
int			start_life(t_rules *rules);
long long	waiting_mini(long long start, long long finish);

#endif
