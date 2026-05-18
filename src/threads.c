/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:37:38 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/19 01:33:05 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->data->nb_coders == 1)
	{
		log_action(coder, "has taken a dongle");
		usleep(coder->data->time_to_burnout * 1000);
		return (NULL);
	}
	if (coder->id % 2 == 0)
		usleep(1000);
	while ((!simulation_stopped(coder->data))
		&& (coder->compil_count < coder->data->required_compiles))
	{
		compile_routine(coder);
		debug_routine(coder);
		refactor_routine(coder);
		pthread_mutex_lock(&coder->data->state_mutex);
		coder->compil_count++;
		pthread_mutex_unlock(&coder->data->state_mutex);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		if (pthread_create(&data->coders[i].thread, NULL, routine,
				&data->coders[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
	free(data->coders);
}

int	simulation_stopped(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->state_mutex);
	return (stop);
}
