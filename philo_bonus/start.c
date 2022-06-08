/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:51:41 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:52 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	start_semaphore(t_rules *rules)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_check_eat");
	rules->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU,
			rules->numbers / 2);
	if (rules->forks <= 0)
		return (1);
	rules->write = sem_open("/philo_write", O_CREAT, S_IRWXU, 1);
	if (rules->write <= 0)
		return (1);
	rules->check_eat = sem_open("/philo_check_eat", O_CREAT, S_IRWXU, 1);
	if (rules->check_eat <= 0)
		return (1);
	return (0);
}

void	start_philo(t_rules *rules)
{
	int	i;

	i = rules->numbers;
	while (--i >= 0)
	{
		rules->philo[i].id = i;
		rules->philo[i].eat_cnt = 0;
		rules->philo[i].last_eat = 0;
		rules->philo[i].rules = rules;
	}
}

int	start(t_rules *rules, int argc, char **argv)
{
	rules->numbers = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->sleep = ft_atoi(argv[4]);
	if (rules->numbers < 1 || rules->numbers > 200 || rules->die < 60
		|| rules->eat < 60 || rules->sleep < 60)
		return (1);
	if (argc == 6)
	{
		rules->n_must_eat = ft_atoi(argv[5]);
		if (rules->n_must_eat <= 0)
			return (1);
	}
	else
		rules->n_must_eat = -1;
	rules->dieded = 0;
	if (start_semaphore(rules))
		return (2);
	start_philo(rules);
	return (0);
}
