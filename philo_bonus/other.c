/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:47:55 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 18:47:58 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	ft_exit(int error_num)
{
	char	*error;

	if (error_num == 1)
		error = "bad arguments";
	if (error_num == 2)
		error = "error semaphore";
	if (error_num == 3)
		error = "error processes";
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (-1);
}

long long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	message(t_rules *rules, int id, char *message)
{
	sem_wait(rules->write);
	if (!(rules->dieded))
		printf("%lli %i %s\n", get_time() - rules->start_time, id + 1, message);
	sem_post(rules->write);
}

long long	waiting_mini(long long start, long long finish)
{
	return (finish - start);
}

void	waiting(long long time, t_rules *rules)
{
	long long	i;

	i = get_time();
	while (!(rules->dieded))
	{
		if (waiting_mini(i, get_time()) >= time)
			return ;
		usleep(100);
	}
}
