/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:05:57 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/19 12:06:23 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if ((strlen(str) == 10 && ft_strcmp(str, "2147483647") > 0 && str[0])
		|| (strlen(str) >= 11))
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	if (atoi(str) < 0)
		return (1);
	return (0);
}

int	fill_data(char **argv, t_data *data)
{
	struct timeval	tv;
	long			start_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->nb_coders = atoi(argv[1]);
	data->time_to_burnout = atoi(argv[2]);
	data->time_to_compil = atoi(argv[3]);
	data->time_to_debug = atoi(argv[4]);
	data->time_to_refactor = atoi(argv[5]);
	data->required_compiles = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	data->start_time = start_time;
	data->stop = 0;
	if (strcmp(argv[8], "fifo") == 0)
	{
		data->scheduler_type = FIFO;
		return (0);
	}
	else if (strcmp(argv[8], "edf") == 0)
	{
		data->scheduler_type = EDF;
		return (0);
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;
	int	n;

	i = 1;
	if (argc != 9)
	{
		return (printf("Error, wrong number of arguments\n"), 1);
	}
	while (i < 7)
	{
		n = atoi(argv[i]);
		if ((i == 1 && n <= 0) || (i == 6 && n <= 0))
			return (printf("Error, arg %d must be > 0\n", i), 1);
		if (is_positive_number(argv[i]) == 1)
			return (printf("Error, arg %d must be >= 0\n", i), 1);
		i++;
	}
	return (fill_data(argv, data));
}
