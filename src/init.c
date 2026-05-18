/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:40:12 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/18 15:32:17 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	init_memory(t_data *data)
{
	data->coders = malloc(sizeof(t_coder) * data->nb_coders);
	if (!data->coders)
	{
		free_all(data);
		return (1);
	}
	data->dongles = malloc(sizeof(t_dongle) * data->nb_coders);
	if (!data->dongles)
	{
		free_all(data);
		return (1);
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
			return (1);
		if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
			return (1);
		data->dongles[i].queue.arr = malloc(sizeof(t_request)
				* data->nb_coders);
		if (!data->dongles[i].queue.arr)
			return (1);
		data->dongles[i].busy = 0;
		data->dongles[i].queue.size = 0;
		data->dongles[i].queue.capacity = data->nb_coders;
		data->dongles[i].arrival_counter = 0;
		data->dongles[i].cooldown_until = 0;
		i++;
	}
	return (0);
}

void	init_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].data = data;
		data->coders[i].last_compile_start = 0;
		data->coders[i].compil_count = 0;
		data->coders[i].left = i;
		data->coders[i].right = (i + 1) % data->nb_coders;
		i++;
	}
}

int	init_all(t_data *data)
{
	if (init_memory(data))
		return (1);
	if (init_mutex(data))
		return (1);
	if (init_dongles(data))
	{
		free(data->coders);
		free(data->dongles);
		return (1);
	}
	init_coders(data);
	return (0);
}
