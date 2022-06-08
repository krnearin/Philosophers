/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:47:16 by krnearin          #+#    #+#             */
/*   Updated: 2022/02/02 18:47:40 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		flag;

	if (argc != 5 && argc != 6)
		return (ft_exit(1));
	flag = start(&rules, argc, argv);
	if (flag)
		return (ft_exit(flag));
	if (start_life(&rules))
		return (ft_exit(3));
	return (0);
}
