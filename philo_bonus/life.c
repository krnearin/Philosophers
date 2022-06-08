/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:45:33 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 18:46:58 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	message(rules, philo->id, "took the fork_r");
	message(rules, philo->id, "took the fork_l");
	sem_wait(rules->check_eat);
	message(rules, philo->id, "is eating");
	philo->last_eat = get_time();
	sem_post(rules->check_eat);
	waiting(rules->eat, rules);
	(philo->eat_cnt)++;
	sem_post(rules->forks);
}

void	*death_check(void *void_p)
{
	t_philo	*p;
	t_rules	*r;

	p = (t_philo *)void_p;
	r = p->rules;
	while (1)
	{
		sem_wait(r->check_eat);
		if (waiting_mini(p->last_eat, get_time()) > r->die)
		{
			message(r, p->id, "died");
			r->dieded = 1;
			sem_wait(r->write);
			exit(1);
		}
		sem_post(r->check_eat);
		if (r->dieded)
			break ;
		if (p->eat_cnt >= r->n_must_eat && r->n_must_eat != -1)
			break ;
	}
	return (NULL);
}

void	*processes_func(void *void_p)
{
	t_rules	*r;
	t_philo	*p;

	p = (t_philo *)void_p;
	r = p->rules;
	p->last_eat = get_time();
	pthread_create(&(p->tread), NULL, death_check, void_p);
	while (!(r->dieded))
	{
		eat(p);
		if (p->eat_cnt >= r->n_must_eat && r->n_must_eat != -1)
			break ;
		message(r, p->id, "is sleeping");
		waiting(r->sleep, r);
		message(r, p->id, "is thinking");
	}
	pthread_join(p->tread, NULL);
	if (r->dieded)
		exit(1);
	exit(0);
}

void	exit_func(t_rules *r)
{
	int	i;
	int	ret;

	waitpid(-1, &ret, 0);
	if (ret != 0)
	{
		i = -1;
		while (++i < r->numbers)
			kill(r->philo[i].processes_id, SIGKILL);
	}
	sem_close(r->forks);
	sem_close(r->write);
	sem_close(r->check_eat);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_check_eat");
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
		philo[i].processes_id = fork();
		if (philo[i].processes_id < 0)
			return (1);
		if (philo[i].processes_id == 0)
			processes_func(&(philo[i]));
	}
	exit_func(rules);
	return (0);
}
