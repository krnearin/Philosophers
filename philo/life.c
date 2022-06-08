/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:59:34 by krnearin          #+#    #+#             */
/*   Updated: 2022/01/25 17:01:08 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	message(rules, philo->id, "took the left fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	message(rules, philo->id, "took the right fork");
	pthread_mutex_lock(&(rules->check_eat));
	message(rules, philo->id, "is eating");
	philo->check_time = get_time();
	pthread_mutex_unlock(&(rules->check_eat));
	waiting(rules->eat, rules);
	(philo->eat_cnt)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
}

void	*pthread_func(void *void_p)
{
	t_philo	*p;
	t_rules	*r;

	p = (t_philo *)void_p;
	r = p->rules;
	if (p->id % 2)
		usleep(100);
	while (!(r->dieded))
	{
		eat(p);
		if (r->check_eat_cnt)
			break ;
		message(r, p->id, "is sleeping");
		waiting(r->sleep, r);
		message(r, p->id, "is thinking");
	}
	return (NULL);
}

void	death_check(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->check_eat_cnt))
	{
		i = -1;
		while (++i < r->numbers && !(r->dieded))
		{
			pthread_mutex_lock(&(r->check_eat));
			if ((get_time() - p[i].check_time) > r->die)
			{
				message(r, p->id, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->check_eat));
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->n_must_eat != -1 && i < r->numbers
			&& p[i].eat_cnt >= r->n_must_eat)
			i++;
		if (i == r->numbers)
			r->check_eat_cnt = 1;
	}
}

void	exit_func(t_philo *p, t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->numbers)
		pthread_join(p->thread_id, NULL);
	i = -1;
	while (++i < r->numbers)
		pthread_mutex_destroy(&(r->forks[i]));
	pthread_mutex_destroy(&(r->write));
	pthread_mutex_destroy(&(r->check_eat));
}

int	start_life(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = rules->philo;
	rules->start_time = get_time();
	while (++i < rules->numbers)
	{
		if (pthread_create(&(philo->thread_id), NULL, pthread_func,
				&(philo[i])))
			return (1);
		philo[i].check_time = get_time();
	}
	death_check(rules, philo);
	exit_func(philo, rules);
	return (0);
}
