/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:09:18 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 20:17:39 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	start_mutex(t_rules *philo)
{
	int	i;

	i = philo->numbers;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(philo->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(philo->write), NULL))
		return (1);
	if (pthread_mutex_init(&(philo->check_eat), NULL))
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
		rules->philo[i].left_fork = (i + 1) % rules->numbers;
		rules->philo[i].right_fork = i;
		rules->philo[i].check_time = 0;
		rules->philo[i].rules = rules;
	}
}

int	start(t_rules *philo, int argc, char **argv)
{
	philo->numbers = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (philo->numbers < 1 || philo->numbers > 200 || philo->die < 60
		|| philo->eat < 60 || philo->sleep < 60)
		return (1);
	if (argc == 6)
	{
		philo->n_must_eat = ft_atoi(argv[5]);
		if (philo->n_must_eat < 0)
			return (1);
	}
	else
		philo->n_must_eat = -1;
	philo->dieded = 0;
	philo->check_eat_cnt = 0;
	if (start_mutex(philo))
		return (2);
	start_philo(philo);
	return (0);
}
