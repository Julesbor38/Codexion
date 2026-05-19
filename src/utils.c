/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:35:28 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/19 12:06:36 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long	timestamp_in_ms(t_coder *coder)
{
	long			actual_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	actual_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (actual_time - coder->data->start_time);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		if (data->dongles[i].queue.arr)
			free(data->dongles[i].queue.arr);
		i++;
	}
	if (data->dongles)
		free(data->dongles);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
