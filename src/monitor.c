/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:08:33 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 14:48:26 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static int	is_done(t_data *data, int i)
{
	if (data->coders[i].compil_count >= data->required_compiles)
		return (1);
	return (0);
}

static int	has_burned_out(t_data *data, int i, long now)
{
	if (now - data->coders[i].last_compile_start > data->time_to_burnout)
		return (1);
	return (0);
}

static int	check_coder(t_data *data, int i, int *done_count)
{
	long	now;

	pthread_mutex_lock(&data->state_mutex);
	now = timestamp_in_ms(&data->coders[i]);
	if (is_done(data, i))
	{
		(*done_count)++;
		pthread_mutex_unlock(&data->state_mutex);
		return (0);
	}
	if (has_burned_out(data, i, now))
	{
		data->stop = 1;
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d burned out\n", now, data->coders[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

static int	all_coders_done(t_data *data, int done_count)
{
	if (done_count == data->nb_coders)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		done_count;

	data = (t_data *)arg;
	while (!data->stop)
	{
		i = 0;
		done_count = 0;
		while (i < data->nb_coders)
		{
			if (check_coder(data, i, &done_count))
				return (NULL);
			i++;
		}
		if (all_coders_done(data, done_count))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
