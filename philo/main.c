/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:53:09 by krnearin          #+#    #+#             */
/*   Updated: 2022/01/26 17:04:02 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	philo;
	int		flag;

	if (argc < 5 || argc > 6)
		return (ft_exit(1));
	flag = start(&philo, argc, argv);
	if (flag)
		return (ft_exit(flag));
	if (start_life(&philo))
		return (ft_exit(3));
	return (0);
}
