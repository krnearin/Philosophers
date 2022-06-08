/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:06:27 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 20:03:22 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					eat_cnt;
	unsigned int		left_fork;
	unsigned int		right_fork;
	long long			check_time;
	pthread_t			thread_id;
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
	int					check_eat_cnt;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		write;
	pthread_mutex_t		check_eat;
	t_philo				philo[200];
}				t_rules;

int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
int					ft_exit(int error_num);
long long			get_time(void);
int					start(t_rules *philo, int argc, char **argv);
void				message(t_rules *rules, int id, char *message);
void				waiting(long long time, t_rules *rules);
long long			waiting_mini(long long start, long long finish);
void				death_check(t_rules *r, t_philo *p);
int					start_life(t_rules *rules);
void				message(t_rules *rules, int id, char *message);
#endif
